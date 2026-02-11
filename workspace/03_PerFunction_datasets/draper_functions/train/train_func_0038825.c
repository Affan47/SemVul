execute()
{
  unsigned int new_value;

  if (access)
      source = cpu_pic->register_bank[register_address];
  else if (cpu16->extended_instruction() && register_address < 0x60)
      source = cpu_pic->registers[register_address + cpu16->ind2.fsr_value];
  else
      source = cpu_pic->registers[register_address];

  new_value = source->get() ^ 0xff;


  if(destination)
    source->put(new_value);
  else
    cpu16->Wput(new_value);

  cpu16->status->put_N_Z(new_value);

  cpu16->pc->increment();

}
