display_text_att(long int msgno, ATTACH_S *a, int flags)
{
    STORE_S  *store;
    HANDLE_S *handles = NULL;
    int       rv = 0;

    if(msgno > 0L)
      clear_index_cache_ent(ps_global->mail_stream, msgno, 0);

    if((store = format_text_att(msgno, a, &handles)) != NULL){
	rv = scroll_attachment("ATTACHED TEXT", store, CharStar, handles, a, flags);
	free_handles(&handles);
	so_give(&store);
    }
    else
      q_status_message(SM_ORDER | SM_DING, 3, 3,
		       _("Error allocating space for attachment."));

    return(rv);
}
