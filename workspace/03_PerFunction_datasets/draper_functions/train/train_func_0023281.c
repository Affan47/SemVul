Note_sendnotification(char *format, ...)
{
	va_list	va;
	userrec	*u;

	Note->send_buf1[0] = 0;
	va_start(va,format);
	vsprintf(Note->send_buf1,format,va);
	va_end(va);

	for(u=User->userlist; u!=NULL; u=u->next)
		if(u->flags & USER_NOTICES)
			Note_sendnotice(u,Note->send_buf1);
}
