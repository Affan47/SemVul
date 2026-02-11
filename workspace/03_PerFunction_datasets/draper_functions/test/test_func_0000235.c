execute()
{
  if(!initialized)
    runtime_initialize();

  cpu16->pc->jump(destination_index);

}
