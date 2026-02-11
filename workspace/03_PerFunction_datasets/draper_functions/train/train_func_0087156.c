display_filename_trans(policydb_t *p, FILE *fp)
{
	filename_trans_t *ft;

	fprintf(fp, "filename_trans rules:\n");
	for (ft = p->filename_trans; ft; ft = ft->next) {
		display_id(p, fp, SYM_TYPES, ft->stype - 1, "");
		display_id(p, fp, SYM_TYPES, ft->ttype - 1, "");
		display_id(p, fp, SYM_CLASSES, ft->tclass - 1, ":");
		display_id(p, fp, SYM_TYPES, ft->otype - 1, "");
		fprintf(fp, " %s\n", ft->name);
	}
}
