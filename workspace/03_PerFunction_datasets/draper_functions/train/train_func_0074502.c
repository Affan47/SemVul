ikrt_select(ikptr fds, ikptr rfds, ikptr wfds, ikptr xfds ){
  int rv = select(unfix(fds),
                  (fd_set*)(rfds + off_bytevector_data),
                  (fd_set*)(wfds + off_bytevector_data),
                  (fd_set*)(xfds + off_bytevector_data),
                  NULL);
  if(rv < 0){
    return ik_errno_to_code();
  }
  return fix(rv);
}
