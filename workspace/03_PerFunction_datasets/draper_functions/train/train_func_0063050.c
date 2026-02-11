init(void)
{
  DEBUG_MSG("DataPool::init(): Initializing\n");
  DEBUG_MAKE_INDENT(3);
  start=0; length=-1; add_at=0;
  eof_flag=false;
  stop_flag=false;
  stop_blocked_flag=false;

  active_readers=new Counter;
  block_list=0;
  G_TRY
  {
    block_list=new BlockList;
    data=ByteStream::create();
  }
  G_CATCH_ALL
  {
    delete block_list;
    block_list=0;
    delete active_readers;
    active_readers=0;
    G_RETHROW;
  }
  G_ENDCATCH;
}
