execute()
{
  if (access)
      source = cpu_pic->register_bank[register_address];
  else if (cpu16->extended_instruction() && register_address < 0x60)
      source = cpu_pic->registers[register_address + cpu16->ind2.fsr_value];
  else
      source = cpu_pic->registers[register_address];

  if(source->get() < cpu16->Wget())
    cpu16->pc->skip();
  else
    cpu16->pc->increment();

}
