imap_get_ssl(MMLOGIN_S *m_list, STRLIST_S *hostlist, int *ok_novalidate, int *warned)
{
    MMLOGIN_S *l;

    for(l = m_list; l; l = l->next)
      if(imap_same_host(l->hosts, hostlist)){
	  if(ok_novalidate)
	    *ok_novalidate = l->ok_novalidate;

	  if(warned)
	    *warned = l->warned;

	  return(TRUE);
      }

    return(FALSE);
}
