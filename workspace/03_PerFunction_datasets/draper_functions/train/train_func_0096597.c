adminfooter(GRSThttpBody *bp, char *dn, char *help_uri, char *dir_uri,
                 char *admin_file)
{
  GRSThttpPrintf(bp, "<p><small>\n");

  if (dn != NULL) GRSThttpPrintf(bp, "<hr>You are %s<br>\n", dn);
  else            GRSThttpPrintf(bp, "<hr>\n");

  if (admin_file != NULL)
       GRSThttpPrintf(bp, "<a href=\"%s%s?cmd=managedir\">"
                      "Manage&nbsp;directory</a> .\n",
                      dir_uri, admin_file);
  else GRSThttpPrintf(bp, "<a href=\"%s\">"
                      "Back&nbsp;to&nbsp;directory</a> .\n", dir_uri);

  if (help_uri != NULL)
    GRSThttpPrintf(bp, "<a href=\"%s\">Website&nbsp;Help</a> .\n", help_uri);

  if ((getenv("GRST_NO_LINK") == NULL) &&
      (getenv("REDIRECT_GRST_NO_LINK") == NULL))
    GRSThttpPrintf(bp, "Built with "
     "<a href=\"http://www.gridsite.org/\">GridSite</a> %s\n",
     VERSION);

  GRSThttpPrintf(bp, "</small>\n");
}
