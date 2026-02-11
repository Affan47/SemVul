write_user_lists (FILE *fp)
{
    int i;

    for (i=0; i<n_vars; i++) {
	if (uvars[i]->type == GRETL_TYPE_LIST) {
	    gretl_xml_put_named_list(uvars[i]->name,
				     uvars[i]->ptr,
				     fp);
	}
    }
}
