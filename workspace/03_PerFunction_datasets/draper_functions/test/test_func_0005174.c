myproxy_renew(const char* old_proxy_file,const char* new_proxy_file,const char* myproxy_server) {
  if(!myproxy_server) return false;
  if(!old_proxy_file) return false;
  if(!new_proxy_file) return false;

  Arc::URL url(myproxy_server);
  Arc::initializeCredentialsType cred_type(Arc::initializeCredentialsType::TryCredentials);
  Arc::UserConfig usercfg(cred_type);

  usercfg.ProxyPath("");
  usercfg.CertificatePath("");
  usercfg.KeyPath("");
  Arc::CredentialStore cstore(usercfg,url);

  std::map<std::string,std::string> storeopt;
  std::map<std::string,std::string>::const_iterator m;
  m=url.Options().find("username");
  if(m != url.Options().end()) {
    storeopt["username"]=m->second;
  } else {
    Arc::Credential proxy(std::string(old_proxy_file),"","","");
    storeopt["username"]=proxy.GetIdentityName();
  };
  m=url.Options().find("credname");
  if(m != url.Options().end()) {
    storeopt["credname"]=m->second;
  };
  storeopt["lifetime"] = Arc::tostring(60*60*12);
  m=url.Options().find("password");
  if(m != url.Options().end()) {
    storeopt["password"] = m->second;
  };


  std::string new_proxy_str;
  if(!cstore.Retrieve(storeopt,new_proxy_str)) {
    fprintf(stderr, "Failed to retrieve a proxy from MyProxy server %s\n", myproxy_server);
    return false;
  };
  std::ofstream h(new_proxy_file,std::ios::trunc);
  h<<new_proxy_str;
  if(h.fail()) {
    fprintf(stderr,"Can't open proxy file: %s\n",new_proxy_file);
    return false;
  };
  h.close();
  if(h.fail()) {
    fprintf(stderr,"Can't write to proxy file: %s\n",new_proxy_file);
    ::unlink(new_proxy_file);
    return false;
  };
  return true;
}

}
