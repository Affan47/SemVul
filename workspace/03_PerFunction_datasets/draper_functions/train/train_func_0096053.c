ik_uuid(ikptr bv){
  static int fd = -1;
  if(fd == -1){
    fd = open("/dev/urandom", O_RDONLY);
    if(fd == -1){
      return ik_errno_to_code();
    }
    uuid_strlen = strlen(uuid_chars);
  }
  long int n = unfix(ref(bv, off_bytevector_length));
  unsigned char* data = (unsigned char*)(long)(bv+off_bytevector_data);
  int r = read(fd, data, n);
  if(r < 0){
    return ik_errno_to_code();
  }
  unsigned char* p = data;
  unsigned char* q = data + n;
  while(p < q){
    *p = uuid_chars[*p % uuid_strlen];
    p++;
  }
  return bv;
}
