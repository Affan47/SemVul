tag_hints(void){
  char **az;
  int cn;
  time_t tx;
  struct tm *pTm;
  char zDateUTC[200];

  login_check_credentials();
  if( !g.okRead ){ login_needed(); return; }
  throttle(1,0);
  cn = atoi(PD("cn","0"));
  az = db_query("SELECT date, branch, milestone, user, message "
                "FROM chng WHERE cn=%d", cn);
  if( az[0]==0 ){ cgi_redirect("index"); return; }
  common_add_action_item( mprintf("chngview?cn=%d",cn), "Back");
  add_chng_tools(0,cn,atoi(az[2]));
  common_header("Tagging And Branching Hints");
  tx = (time_t)atoi(az[0])-1;
  pTm = gmtime(&tx);
  strftime(zDateUTC, sizeof(zDateUTC), "%Y-%m-%d %H:%M:%S UTC", pTm);
  cgi_printf("<p>To create a tag that occurs <i>before</i> \n"
         "check-in <a href=\"chngview?cn=%d\">[%d]</a>, go to the root of\n"
         "the source tree and enter the following CVS command:</p>\n"
         "<blockquote>\n"
         "<tt>cvs rtag -D '%s' </tt><i>&lt;tag-name&gt;</i><tt> .</tt>\n"
         "</blockquote>\n"
         "\n"
         "<p>Be careful to include the dot (\".\") at the end of the line!\n"
         "To create a branch that occurs before the check-in, enter this \n"
         "command:</p>\n"
         "<blockquote>\n"
         "<tt>cvs rtag -b -D '%s' </tt><i>&lt;branch-name&gt;</i><tt> .</tt>\n"
         "</blockquote>\n",cn,cn,zDateUTC,zDateUTC);
  common_footer();
}
