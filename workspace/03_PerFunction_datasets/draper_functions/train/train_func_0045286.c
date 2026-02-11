fix_proxy_nid(X509* cert,int nid,int gnid) {
    if(cert == NULL) return;
    STACK_OF(X509_EXTENSION) * extensions = cert->cert_info->extensions;
    if(extensions == NULL) return;
    int num = sk_X509_EXTENSION_num(extensions);
    for(int i=0;i<num;++i) {
      X509_EXTENSION* ext = sk_X509_EXTENSION_value(extensions,i);
      fix_proxy_nid(ext,nid,gnid);
    }
  }
