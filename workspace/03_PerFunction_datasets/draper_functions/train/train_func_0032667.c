webcmd_reply()
{
	char	tmp[BUFSIZ];
	int	num;
	noterec	*n;
	nbody	*body;


	sprintf(tmp,"%s - Note %s",Web->title,Web->tok1);
	openhtml(tmp);
	websay_statusline();
	sprintf(tmp,"Reply:%s",Web->tok1);
	websay_menuline(tmp);
	websay("<br><br>");
	websay("");

	websay("<form method=\"post\" action=\"%s?%s;%s;!note_post\">",Web->cgi_url,Web->user->acctname,Web->user->pass);


	num = atoi(Web->tok1);
	n = Note_notebynumber(Web->user,num);
	if(n == NULL)
	{
		websay("Note %d doesn't exist anymore!",num);
		closehtml();
		return;
	}


	websay("<font face=\"arial\" size=\"2\"><b><a href=\"%s?%s;%s;Finger:%s\">%s</a> said:</b></font><br>",Web->cgi_url,Web->user->acctname,Web->user->pass,n->nick,n->nick);
	websay("<table width=570 border=0><tr><td>");
	for(body=n->body; body!=NULL; body=body->next)
	{
		if(body->text[0])
		{
			strcpy(tmp, body->text);
			Web_fixforhtml(tmp);
			websay("%s",tmp);
		}
		else
			websay("<p>");
	}
	websay("</td></tr></table>");
	websay("<br>");
	websay("");

	websay("<input type=\"hidden\" name=\"nick\" value=\"%s\">",n->nick);
	websay("<font face=\"arial\" size=\"2\"><b>Your reply:</b></font>");
	websay("<br>");
	websay("<textarea wrap=\"virtual\" name=\"body\" rows=7 cols=67></textarea><p>");
	websay("<input type=\"submit\" value=\"Send Note\"> <input type=\"reset\" value=\"Clear\"><br><br");

	closehtml();
}
