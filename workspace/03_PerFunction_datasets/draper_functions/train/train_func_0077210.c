wikinew_page(void){
  const char *zName;
  const char *zMimetype;
  login_check_credentials();
  if( !g.perm.NewWiki ){
    login_needed();
    return;
  }
  zName = PD("name","");
  zMimetype = wiki_filter_mimetypes(P("mimetype"));
  if( zName[0] && wiki_name_is_wellformed((const unsigned char *)zName) ){
    if( fossil_strcmp(zMimetype,"text/x-fossil-wiki")==0
     && db_get_boolean("wysiwyg-wiki", 0)
    ){
      cgi_redirectf("wikiedit?name=%T&wysiwyg=1", zName);
    }else{
      cgi_redirectf("wikiedit?name=%T&mimetype=%s", zName, zMimetype);
    }
  }
  style_header("Create A New Wiki Page");
  cgi_printf("<p>Rules for wiki page names:</p>\n");
  well_formed_wiki_name_rules();
  form_begin(0, "%R/wikinew");
  cgi_printf("<p>Name of new wiki page:\n"
         "<input style=\"width: 35;\" type=\"text\" name=\"name\" value=\"%h\" /><br />\n",(zName));
  mimetype_option_menu("text/x-fossil-wiki");
  cgi_printf("<br /><input type=\"submit\" value=\"Create\" />\n"
         "</p></form>\n");
  if( zName[0] ){
    cgi_printf("<p><span class=\"wikiError\">\n"
           "\"%h\" is not a valid wiki page name!</span></p>\n",(zName));
  }
  style_footer();
}
