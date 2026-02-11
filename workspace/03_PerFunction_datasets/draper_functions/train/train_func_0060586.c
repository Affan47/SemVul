row_sel_sec_rec_is_for_clust_rec(

	const rec_t*	sec_rec,
	dict_index_t*	sec_index,
	const rec_t*	clust_rec,


	dict_index_t*	clust_index)
{
	const byte*	sec_field;
	ulint		sec_len;
	const byte*	clust_field;
	ulint		n;
	ulint		i;
	mem_heap_t*	heap		= NULL;
	ulint		clust_offsets_[REC_OFFS_NORMAL_SIZE];
	ulint		sec_offsets_[REC_OFFS_SMALL_SIZE];
	ulint*		clust_offs	= clust_offsets_;
	ulint*		sec_offs	= sec_offsets_;
	ibool		is_equal	= TRUE;

	rec_offs_init(clust_offsets_);
	rec_offs_init(sec_offsets_);

	if (rec_get_deleted_flag(clust_rec,
				 dict_table_is_comp(clust_index->table))) {


		return(FALSE);
	}

	clust_offs = rec_get_offsets(clust_rec, clust_index, clust_offs,
				     ULINT_UNDEFINED, &heap);
	sec_offs = rec_get_offsets(sec_rec, sec_index, sec_offs,
				   ULINT_UNDEFINED, &heap);

	n = dict_index_get_n_ordering_defined_by_user(sec_index);

	for (i = 0; i < n; i++) {
		const dict_field_t*	ifield;
		const dict_col_t*	col;
		ulint			clust_pos;
		ulint			clust_len;
		ulint			len;

		ifield = dict_index_get_nth_field(sec_index, i);
		col = dict_field_get_col(ifield);
		clust_pos = dict_col_get_clust_pos(col, clust_index);

		clust_field = rec_get_nth_field(
			clust_rec, clust_offs, clust_pos, &clust_len);
		sec_field = rec_get_nth_field(sec_rec, sec_offs, i, &sec_len);

		len = clust_len;

		if (ifield->prefix_len > 0 && len != UNIV_SQL_NULL
		    && sec_len != UNIV_SQL_NULL) {

			if (rec_offs_nth_extern(clust_offs, clust_pos)) {
				len -= BTR_EXTERN_FIELD_REF_SIZE;
			}

			len = dtype_get_at_most_n_mbchars(
				col->prtype, col->mbminmaxlen,
				ifield->prefix_len, len, (char*) clust_field);

			if (rec_offs_nth_extern(clust_offs, clust_pos)
			    && len < sec_len) {
				if (!row_sel_sec_rec_is_for_blob(
					    col->mtype, col->prtype,
					    col->mbminmaxlen,
					    clust_field, clust_len,
					    sec_field, sec_len,
					    ifield->prefix_len,
					    clust_index->table)) {
					goto inequal;
				}

				continue;
			}
		}

		if (0 != cmp_data_data(col->mtype, col->prtype,
				       clust_field, len,
				       sec_field, sec_len)) {
inequal:
			is_equal = FALSE;
			goto func_exit;
		}
	}

func_exit:
	if (UNIV_LIKELY_NULL(heap)) {
		mem_heap_free(heap);
	}
	return(is_equal);
}
