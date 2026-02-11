ikrt_getcwd(ikpcb* pcb){
  char buff[MAXPATHLEN+1];
  char* path = getcwd(buff, MAXPATHLEN);
  if(! path){
    return ik_errno_to_code();
  }
  int len = strlen(path);
  ikptr bv = ik_safe_alloc(pcb, align(disp_bytevector_data+len+1));
  ref(bv,0) = fix(len);
  memcpy(disp_bytevector_data+(char*)(bv), path, len+1);
  return bv+bytevector_tag;
}
