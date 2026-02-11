plugin_mr_filter_create (mr_filter_t* f)
{
    int rc = LDAP_UNAVAILABLE_CRITICAL_EXTENSION;
    struct slapdplugin* mrp = plugin_mr_find_registered (f->mrf_oid);
    Slapi_PBlock pb;

    if (mrp != NULL)
    {
		rc = attempt_mr_filter_create (f, mrp, &pb);
    }
    else
    {

		for (mrp = get_plugin_list(PLUGIN_LIST_MATCHINGRULE); mrp != NULL; mrp = mrp->plg_next)
		{
		    if (!(rc = attempt_mr_filter_create (f, mrp, &pb)))
		    {
				plugin_mr_bind (f->mrf_oid, mrp);
				break;
		    }
		}
    }
    if (rc)
    {

		mrp = plugin_mr_find(f->mrf_oid);
		if (mrp)
		{

		    pblock_init(&pb);
		    slapi_pblock_set(&pb, SLAPI_PLUGIN, mrp);
		    slapi_pblock_set(&pb, SLAPI_PLUGIN_MR_FILTER_CREATE_FN, default_mr_filter_create);
		    if (!(rc = attempt_mr_filter_create (f, mrp, &pb)))
		    {
				plugin_mr_bind (f->mrf_oid, mrp);
		    }
		}
    }
    if (!rc)
    {

		slapi_pblock_get (&pb, SLAPI_PLUGIN_MR_FILTER_INDEX_FN, &(f->mrf_index));
		slapi_pblock_get (&pb, SLAPI_PLUGIN_MR_FILTER_REUSABLE, &(f->mrf_reusable));
		slapi_pblock_get (&pb, SLAPI_PLUGIN_MR_FILTER_RESET_FN, &(f->mrf_reset));
		slapi_pblock_get (&pb, SLAPI_PLUGIN_OBJECT, &(f->mrf_object));
		slapi_pblock_get (&pb, SLAPI_PLUGIN_DESTROY_FN, &(f->mrf_destroy));
    }
    return rc;
}
