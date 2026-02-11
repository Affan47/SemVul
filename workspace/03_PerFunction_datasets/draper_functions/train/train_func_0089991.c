execute()
{
  unsigned int new_value;

  if(!access)
    source = cpu_pic->registers[register_address];
  else
    source = cpu_pic->register_bank[register_address];

  new_value = (source->get() << 1) | cpu_pic->status->get_C();

  if(destination)
    source->put(new_value&0xff);
  else
    cpu_pic->Wput(new_value&0xff);

  cpu_pic->status->put_C(new_value>0xff);

  cpu_pic->pc->increment();

}
