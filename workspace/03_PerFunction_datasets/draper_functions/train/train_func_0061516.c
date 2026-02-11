RFCNB_Hangup(struct RFCNB_Con *con_Handle)

{
  struct redirect_addr *redir_addr,*next;

  if (con_Handle != NULL) {
    RFCNB_Close(con_Handle -> fd);
    if (con_Handle -> redirect_list != NULL)
    {
	do {
		redir_addr = con_Handle->redirect_list;
		next = redir_addr->next;
		free(redir_addr);
	} while(next!=NULL);
	}
    free(con_Handle);
  }

  return 0;


}
