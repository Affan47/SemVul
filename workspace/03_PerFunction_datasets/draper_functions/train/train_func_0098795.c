passwd_callback(char *buf, int num, int encrypting
#ifdef HAVE_USERDATA_IN_PWD_CALLBACK


                           , void *global_passwd
#endif
                           )
{
  DEBUGASSERT(0 == encrypting);

  if(!encrypting) {
    int klen = curlx_uztosi(strlen((char *)global_passwd));
    if(num > klen) {
      memcpy(buf, global_passwd, klen+1);
      return klen;
    }
  }
  return 0;
}
