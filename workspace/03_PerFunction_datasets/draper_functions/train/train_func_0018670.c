hyperlink_to_diff(const char *zV1, const char *zV2){
  if( g.perm.Hyperlink ){
    if( zV2==0 ){
      cgi_printf("%z[diff]</a>\n",(href("%R/diff?v2=%s",zV1)));
    }else{
      cgi_printf("%z[diff]</a>\n",(href("%R/diff?v1=%s&v2=%s",zV1,zV2)));
    }
  }
}
