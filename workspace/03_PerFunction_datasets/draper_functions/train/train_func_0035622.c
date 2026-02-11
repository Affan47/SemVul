fix_proxy_nid(STACK_OF(X509)* chain,int nid,int gnid) {
    if(chain == NULL) return;
    int num = sk_X509_num(chain);
    for(int i=0;i<num;++i) {
      X509* cert = sk_X509_value(chain,i);
      fix_proxy_nid(cert,nid,gnid);
    }
  }
