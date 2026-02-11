stun_attr_add_str(u08bits* buf, size_t *len, u16bits attr, const u08bits* avalue, int alen) {
  if(alen<0) alen=0;
  u08bits tmp[1];
  if(!avalue) {
    alen=0;
    avalue=tmp;
  }
  int clen = stun_get_command_message_len_str(buf,*len);
  int newlen = clen + 4 + alen;
  int newlenrem4=newlen & 0x00000003;
  if(newlenrem4) {
    newlen=newlen+(4-newlenrem4);
  }
  if(newlen>=MAX_STUN_MESSAGE_SIZE) return -1;
  else {
    u08bits* attr_start=buf+clen;

    u16bits *attr_start_16t=(u16bits*)attr_start;

    stun_set_command_message_len_str(buf,newlen);
    *len = newlen;

    attr_start_16t[0]=nswap16(attr);
    attr_start_16t[1]=nswap16(alen);
    if(alen>0) ns_bcopy(avalue,attr_start+4,alen);
    return 0;
  }
}
