GDtoNet(GopherDirObj *gd, int sockfd, GSformat fmt, char *ticket,
	void (*prefcn)())
{
     int i;
     GopherObj *gs;
     Debugmsg("GDplustoNet\n");

     if (fmt == GSFORM_HTML) {
	  writestring(sockfd, "<DL COMPACT>\r\n");
     }

     for (i=0; i< GDgetNumitems(gd); i++) {
	  gs = GDgetEntry(gd, i);
	  if (fmt == GSFORM_HTML)
	       writestring(sockfd, "<DT>");

	  if (prefcn)
	       prefcn(gs, sockfd);
	  GStoNet(GDgetEntry(gd, i), sockfd, fmt, ticket);
     }

     if (fmt == GSFORM_HTML) {
	  writestring(sockfd, "</DL>\r\n");
     }
}
