execute()
{
  unsigned int value;

  if (access)
      source = cpu_pic->register_bank[register_address];
  else if (cpu16->extended_instruction() && register_address < 0x60)
      source = cpu_pic->registers[register_address + cpu16->ind2.fsr_value];
  else
      source = cpu_pic->registers[register_address];


  value = (0xff & cpu16->Wget()) * (0xff & source->get());

  cpu16->prodl.put(value &0xff);
  cpu16->prodh.put((value>>8) &0xff);

  cpu16->pc->increment();

}
