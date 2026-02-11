open_globus_policy(const X509_NAME* issuer_subject,const std::string& ca_path) {
  std::string issuer_subject_str;
  X509_NAME_to_string(issuer_subject_str,issuer_subject);
  unsigned long hash = X509_NAME_hash((X509_NAME*)issuer_subject);
  char hash_str[32];
  snprintf(hash_str,sizeof(hash_str)-1,"%08lx",hash);
  hash_str[sizeof(hash_str)-1]=0;
  std::string fname = ca_path+"/"+hash_str+policy_suffix;
  std::ifstream* f = new std::ifstream(fname.c_str());
  if(!(*f)) { delete f; return NULL; };
  return f;
}

}
