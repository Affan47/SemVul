http_build_login_card(Blob *pPayload, Blob *pLogin){
  Blob nonce;
  const char *zLogin;
  const char *zPw;
  Blob pw;
  Blob sig;

  blob_zero(pLogin);
  if( g.urlUser==0 || fossil_strcmp(g.urlUser, "anonymous")==0 ){
     return;
  }
  if( g.urlIsSsh ){
     return;
  }
  blob_zero(&nonce);
  blob_zero(&pw);
  sha1sum_blob(pPayload, &nonce);
  blob_copy(&pw, &nonce);
  zLogin = g.urlUser;
  if( g.urlPasswd ){
    zPw = g.urlPasswd;
  }else if( g.cgiOutput ){

    cgi_printf("*** incorrect or missing password for user %h\n", zLogin);
    zPw = 0;
  }else{

    url_prompt_for_password();
    zPw = g.urlPasswd;
  }


  if( zPw && zPw[0]=='#' ) zPw++;


  if( zPw && zPw[0] ) zPw = sha1_shared_secret(zPw, zLogin, 0);

  blob_append(&pw, zPw, -1);
  sha1sum_blob(&pw, &sig);
  blob_appendf(pLogin, "login %F %b %b\n", zLogin, &nonce, &sig);
  blob_reset(&pw);
  blob_reset(&sig);
  blob_reset(&nonce);
}
