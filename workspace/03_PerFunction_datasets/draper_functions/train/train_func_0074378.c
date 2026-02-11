eb_appendix_subbook_list(EB_Appendix *appendix, EB_Subbook_Code *subbook_list,
    int *subbook_count)
{
    EB_Error_Code error_code;
    EB_Subbook_Code *list_p;
    int i;

    eb_lock(&appendix->lock);
    LOG(("in: eb_appendix_subbook_list(appendix=%d)", (int)appendix->code));


    if (appendix->path == NULL) {
	error_code = EB_ERR_UNBOUND_APP;
	goto failed;
    }


    for (i = 0, list_p = subbook_list; i < appendix->subbook_count;
	 i++, list_p++)
	*list_p = i;
    *subbook_count = appendix->subbook_count;

    LOG(("out: eb_appendix_subbook_list(subbook_count=%d) = %s",
	*subbook_count, eb_error_string(EB_SUCCESS)));
    eb_unlock(&appendix->lock);

    return EB_SUCCESS;


  failed:
    *subbook_count = 0;
    LOG(("out: eb_appendix_subbook_list() = %s", eb_error_string(error_code)));
    eb_unlock(&appendix->lock);
    return error_code;
}
