toast_save_datum(Relation rel, Datum value,
				 bool use_wal, bool use_fsm)
{
	Relation	toastrel;
	Relation	toastidx;
	HeapTuple	toasttup;
	TupleDesc	toasttupDesc;
	Datum		t_values[3];
	bool		t_isnull[3];
	CommandId	mycid = GetCurrentCommandId(true);
	struct varlena *result;
	struct varatt_external toast_pointer;
	struct
	{
		struct varlena hdr;
		char		data[TOAST_MAX_CHUNK_SIZE];
		int32		align_it;
	}			chunk_data;
	int32		chunk_size;
	int32		chunk_seq = 0;
	char	   *data_p;
	int32		data_todo;


	toastrel = heap_open(rel->rd_rel->reltoastrelid, RowExclusiveLock);
	toasttupDesc = toastrel->rd_att;
	toastidx = index_open(toastrel->rd_rel->reltoastidxid, RowExclusiveLock);


	if (VARATT_IS_SHORT(value))
	{
		data_p = VARDATA_SHORT(value);
		data_todo = VARSIZE_SHORT(value) - VARHDRSZ_SHORT;
		toast_pointer.va_rawsize = data_todo + VARHDRSZ;
		toast_pointer.va_extsize = data_todo;
	}
	else if (VARATT_IS_COMPRESSED(value))
	{
		data_p = VARDATA(value);
		data_todo = VARSIZE(value) - VARHDRSZ;

		toast_pointer.va_rawsize = VARRAWSIZE_4B_C(value) + VARHDRSZ;
		toast_pointer.va_extsize = data_todo;

		Assert(VARATT_EXTERNAL_IS_COMPRESSED(toast_pointer));
	}
	else
	{
		data_p = VARDATA(value);
		data_todo = VARSIZE(value) - VARHDRSZ;
		toast_pointer.va_rawsize = VARSIZE(value);
		toast_pointer.va_extsize = data_todo;
	}

	toast_pointer.va_valueid = GetNewOidWithIndex(toastrel, toastidx);
	toast_pointer.va_toastrelid = rel->rd_rel->reltoastrelid;


	t_values[0] = ObjectIdGetDatum(toast_pointer.va_valueid);
	t_values[2] = PointerGetDatum(&chunk_data);
	t_isnull[0] = false;
	t_isnull[1] = false;
	t_isnull[2] = false;


	while (data_todo > 0)
	{


		chunk_size = Min(TOAST_MAX_CHUNK_SIZE, data_todo);


		t_values[1] = Int32GetDatum(chunk_seq++);
		SET_VARSIZE(&chunk_data, chunk_size + VARHDRSZ);
		memcpy(VARDATA(&chunk_data), data_p, chunk_size);
		toasttup = heap_form_tuple(toasttupDesc, t_values, t_isnull);

		heap_insert(toastrel, toasttup, mycid, use_wal, use_fsm);


		index_insert(toastidx, t_values, t_isnull,
					 &(toasttup->t_self),
					 toastrel, toastidx->rd_index->indisunique);


		heap_freetuple(toasttup);


		data_todo -= chunk_size;
		data_p += chunk_size;
	}


	index_close(toastidx, RowExclusiveLock);
	heap_close(toastrel, RowExclusiveLock);


	result = (struct varlena *) palloc(TOAST_POINTER_SIZE);
	SET_VARSIZE_EXTERNAL(result, TOAST_POINTER_SIZE);
	memcpy(VARDATA_EXTERNAL(result), &toast_pointer, sizeof(toast_pointer));

	return PointerGetDatum(result);
}
