QCC_PR_EmitFieldsForMembers(QCC_type_t *clas)
{


	char membername[2048];
	int p, np, a;
	unsigned int o;
	QCC_type_t *mt, *ft;
	QCC_def_t *f, *m;
	if (clas->parentclass != type_entity)
		QCC_PR_EmitFieldsForMembers(clas->parentclass);

	np = clas->num_parms;
	mt = clas->param;
	for (p = 0; p < np; p++, mt = mt->next)
	{
		sprintf(membername, "%s::"MEMBERFIELDNAME, clas->name, mt->name);
		m = QCC_PR_GetDef(NULL, membername, NULL, false, 0, false);

		f = QCC_MemberInParentClass(mt->name, clas->parentclass);
		if (f)
		{
			if (m->arraysize>1)
				QCC_Error(ERR_INTERNAL, "FTEQCC does not support overloaded arrays of members");
			a=0;
			for (o = 0; o < m->type->size; o++)
				((int *)qcc_pr_globals)[o+a*mt->size+m->ofs] = ((int *)qcc_pr_globals)[o+f->ofs];
			continue;
		}

		for (a = 0; a < m->arraysize; a++)
		{

			ft = QCC_PR_NewType(basictypenames[mt->type], ev_field);
			ft->aux_type = QCC_PR_NewType(basictypenames[mt->type], mt->type);
			ft->aux_type->aux_type = type_void;
			ft->size = ft->aux_type->size;
			ft = QCC_PR_FindType(ft);
			sprintf(membername, "__f_%s_%i", ft->name, ++basictypefield[mt->type]);
			f = QCC_PR_GetDef(ft, membername, NULL, true, 1, true);

			for (o = 0; o < m->type->size; o++)
				((int *)qcc_pr_globals)[o+a*mt->size+m->ofs] = ((int *)qcc_pr_globals)[o+f->ofs];

			f->references++;
		}
	}
}
