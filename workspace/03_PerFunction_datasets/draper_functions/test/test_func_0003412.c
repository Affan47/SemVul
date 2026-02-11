create_full(void)
{
  GP<DjVuMessageLite> &static_message=getDjVuMessageLite();
  if(!static_message)
  {
    DjVuMessage *mesg=new DjVuMessage;
    static_message=mesg;
    mesg->init();
  }
  return DjVuMessageLite::create_lite();
}
