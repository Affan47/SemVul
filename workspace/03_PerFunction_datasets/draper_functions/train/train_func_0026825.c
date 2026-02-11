extractRelOptions(HeapTuple tuple, TupleDesc tupdesc, Oid amoptions)
{
	bytea	   *options;
	bool		isnull;
	Datum		datum;
	Form_pg_class classForm;

	datum = fastgetattr(tuple,
						Anum_pg_class_reloptions,
						tupdesc,
						&isnull);
	if (isnull)
		return NULL;

	classForm = (Form_pg_class) GETSTRUCT(tuple);


	switch (classForm->relkind)
	{
		case RELKIND_RELATION:
		case RELKIND_TOASTVALUE:
		case RELKIND_UNCATALOGED:
			options = heap_reloptions(classForm->relkind, datum, false);
			break;
		case RELKIND_INDEX:
			options = index_reloptions(amoptions, datum, false);
			break;
		default:
			Assert(false);
			options = NULL;
			break;
	}

	return options;
}
