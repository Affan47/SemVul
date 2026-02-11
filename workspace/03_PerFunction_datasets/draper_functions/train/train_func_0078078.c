setup_markupedit_page(void){
  const char *zMarkup = PD("m","");
  const char *zType = PD("t","0");
  const char *zFormat = PD("f","");
  const char *zDescription = PD("d","");
  int delete = atoi(PD("del","0"));


  login_check_credentials();
  if( !g.okSetup ){
    cgi_redirect("setup");
    return;
  }

  common_add_nav_item("setup", "Main Setup Menu");
  common_add_action_item("setup_markup", "Cancel");
  common_add_action_item(mprintf("setup_markupedit?m=%h&del=1",zMarkup),
                         "Delete");
  common_add_help_item("CvstracAdminMarkup");
  common_header("Custom Wiki Markup");

  if( P("can") ){
    cgi_redirect("setup_markup");
    return;
  }else if( P("ok") ){

    db_execute("DELETE FROM markup WHERE markup='%q';", zMarkup);
    cgi_redirect("setup_markup");
    return;
  }else if( delete && zMarkup[0] ){
    cgi_printf("<p>Are you sure you want to delete markup <b>%h</b>?</p>\n"
           "\n"
           "<form method=\"POST\" action=\"setup_markupedit\">\n"
           "<input type=\"hidden\" name=\"m\" value=\"%h\">\n"
           "<input type=\"submit\" name=\"ok\" value=\"Yes, Delete\">\n"
           "<input type=\"submit\" name=\"can\" value=\"No, Cancel\">\n"
           "</form>\n",zMarkup,zMarkup);
    common_footer();
    return;
  }

  if( P("u") ){
    if( zMarkup[0] && zType[0] && zFormat[0] ) {


      db_execute("REPLACE INTO markup(markup,type,formatter,description) "
                 "VALUES('%q',%d,'%q','%q');",
                 zMarkup, atoi(zType), zFormat, zDescription);
    }

    cgi_redirect("setup_markup");
    return;
  }

  if( zMarkup[0] ){


    char **az = db_query("SELECT type, formatter, description "
                         "FROM markup WHERE markup='%q';",
                         zMarkup);
    if( az && az[0] && az[1] && az[2] ){
      zType = az[0];
      zFormat = az[1];
      zDescription = az[2];
    }
  }

  cgi_printf("<form action=\"%s\" method=\"POST\">\n"
         "Markup Name: <input type=\"text\" name=\"m\" value=\"%h\" size=12>\n",g.zPath,zMarkup);
  cgi_optionmenu(0,"t",zType, "Markup","0", "Block","2",
    "Program Markup","1", "Program Block","3", NULL);
  cgi_printf("<br>Formatter:<br>\n"
         "<textarea name=\"f\" rows=\"4\" cols=\"60\">%h</textarea><br>\n"
         "Description:<br>\n"
         "<textarea name=\"d\" rows=\"4\" cols=\"60\">%h</textarea><br>\n"
         "<input type=\"hidden\" name=\"u\">\n"
         "<input type=\"submit\" value=\"Set\">\n"
         "</form>\n"
         "\n"
         "<table border=1 cellspacing=0 cellpadding=5 align=\"right\" width=\"45%%\">\n"
         "<tr><td bgcolor=\"#e0c0c0\">\n"
         "<big><b>Important Security Note</b></big>\n"
         "\n"
         "<p>Program formatters execute external scripts and programs and\n"
         "improper configuration may result in a compromised server.</p>\n"
         "\n"
         "<p>Be sure to enclose all text substitutions in single-quotes.\n"
         "(ex <tt>'%%k'</tt>)  Otherwise, a user could cause arbitrary shell\n"
         "commands to be run on your system.</p>\n"
         " \n"
         "<p>Text is stripped of all single-quotes and backslashs before it is\n"
         "substituted, so if the substitution is itself enclosed in single-quotes,\n"
         "it will always be treated as a single token by the shell.</p>\n"
         "</td></tr></table>\n"
         "\n"
         "The following substitutions are made on the custom markup:\n"
         "<blockquote>\n"
         "<table cellspacing=\"5\" cellpadding=\"0\">\n"
         "<tr><td width=\"40\"><b>%%m</b></td><td>markup name</td></tr>\n"
         "<tr><td><b>%%k</b></td><td>markup key</td></tr>\n"
         "<tr><td><b>%%a</b></td><td>markup arguments</td></tr>\n"
         "<tr><td><b>%%x</b></td><td>markup arguments or, if empty, key</td></tr>\n"
         "<tr><td><b>%%b</b></td><td>markup block</td></tr>\n"
         "<tr><td><b>%%r</b></td><td>%s repository root</td></tr>\n"
         "<tr><td><b>%%n</b></td><td>CVSTrac project name</td></tr>\n"
         "<tr><td><b>%%u</b></td><td>Current user</td></tr>\n"
         "<tr><td><b>%%c</b></td><td>User capabilities</td></tr>\n"
         "</table>\n"
         "</blockquote>\n"
         "\n"
         "Additionally, external programs have some or all the following\n"
         "environment variables defined:<br>\n"
         "REQUEST_METHOD, GATEWAY_INTERFACE, REQUEST_URI, PATH_INFO,\n"
         "QUERY_STRING, REMOTE_ADDR, HTTP_USER_AGENT, CONTENT_LENGTH,\n"
         "HTTP_REFERER, HTTP_HOST, CONTENT_TYPE, HTTP_COOKIE\n"
         "<br>\n"
         "\n"
         "<h2>Notes</h2>\n"
         "<ul>\n"
         "  <li>The markup name is the wiki formatting tag. i.e. a markup named\n"
         "  <b>echo</b> would be invoked using <tt>{echo: key args}</tt></li>\n"
         "  <li>Changing the name of an existing markup may break existing\n"
         "  wiki pages</li>\n"
         "  <li>\"Markup\" markups are simple string substitutions and are handled\n"
         "  directly by CVSTrac</li>\n"
         "  <li>\"Block\" markups are paired {markup} and {endmarkup} which get\n"
         "  all the text in between as arguments (%a), with no key.</li>\n"
         "  <li>\"Program\" markups are handled by running external scripts and\n"
         "  programs. These are more flexible, but there are security risks and\n"
         "  too many may slow down page creation. A Program Markup gets the\n"
         "  arguments on the command line while a Program Block also gets the block\n"
         "  from standard input. Both forms should write HTML to standard output</li>\n"
         "  <li>The Description field is used when enumerating the list of available\n"
         "  custom markups using the {markups} tag. This is included in pages\n"
         "  such as <a href=\"wiki?p=WikiFormatting\">WikiFormatting</a> in order to\n"
         "  document server-specific markups.</li>\n"
         "</ul>\n",zFormat,zDescription,g.scm.zName);

  common_footer();
}
