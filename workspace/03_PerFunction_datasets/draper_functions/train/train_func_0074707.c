AIO_OfxGroup_STATUS__getErrorStruct(int e) {
  int i;

  for (i=0; ; i++) {
    if (error_msg_list[i].code==e)
      return &error_msg_list[i];

    if (error_msg_list[i].code==-1)
      break;
  }
  return NULL;
}
