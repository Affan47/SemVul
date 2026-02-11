write(unsigned char *buf,unsigned long long int offset,unsigned long long int size) {
  ssize_t l;
  size_t ll;
  logger.msg(Arc::VERBOSE, "plugin: write");
  if(data_file == -1) return 1;
  if(lseek(data_file,offset,SEEK_SET) != offset) {
    perror("lseek");
    return 1;
  };
  for(ll=0;ll<size;ll+=l) {
    if((l=::write(data_file,buf+ll,size-ll)) == -1) {
      perror("write");
      return 1;
    };
    if(l==0) logger.msg(Arc::WARNING, "Zero bytes written to file");
  };
  return 0;
}
