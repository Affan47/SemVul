job_mark_add(const std::string &fname,const std::string &content) {
  int h=open(fname.c_str(),O_WRONLY | O_CREAT | O_APPEND,S_IRUSR | S_IWUSR);
  if(h==-1) return false;
  write(h,(const void *)content.c_str(),content.length());
  close(h); return true;
}
