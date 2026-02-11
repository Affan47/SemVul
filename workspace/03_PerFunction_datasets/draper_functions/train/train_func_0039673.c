nxt_mod_read_low(nxt_t *nxt,int modid,void *buf,size_t offset,size_t size) {
  nxt_pack_start(nxt,0x94);
  nxt_pack_dword(nxt,modid);
  nxt_pack_word(nxt,offset);
  nxt_pack_word(nxt,size);
  test(nxt_con_send(nxt));
  test(nxt_con_recv(nxt,9+size));
  test(nxt_unpack_start(nxt,0x94));
  if (nxt_unpack_error(nxt)==0) {
    nxt_unpack_dword(nxt);
    size = nxt_unpack_word(nxt);
    memcpy(buf,nxt_unpack_mem(nxt,size),size);
    return size;
  }
  else return NXT_FAIL;
}
