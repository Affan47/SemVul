Put(const char* buf,Size_t size) {

  ssize_t l;
  if(ssl_ == NULL) return false;
  for(;size;){
     l=SSL_write(ssl_,buf,size);
     if(l <= 0){
        SetFailure(SSL_get_error(ssl_,l));
        return false;
     }
     buf+=l; size-=l;
  }
  return true;
}
