heap_reloptions(char relkind, Datum reloptions, bool validate)
{
	StdRdOptions *rdopts;

	switch (relkind)
	{
		case RELKIND_TOASTVALUE:
			rdopts = (StdRdOptions *)
				default_reloptions(reloptions, validate, RELOPT_KIND_TOAST);
			if (rdopts != NULL)
			{

				rdopts->fillfactor = 100;
				rdopts->autovacuum.analyze_threshold = -1;
				rdopts->autovacuum.analyze_scale_factor = -1;
			}
			return (bytea *) rdopts;
		case RELKIND_RELATION:
			return default_reloptions(reloptions, validate, RELOPT_KIND_HEAP);
		default:

			return NULL;
	}
}
