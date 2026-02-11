execute()
{
  unsigned int new_value,src_value,w_value;

  if (access)
      source = cpu_pic->register_bank[register_address];
  else if (cpu16->extended_instruction() && register_address < 0x60)
      source = cpu_pic->registers[register_address + cpu16->ind2.fsr_value];
  else
      source = cpu_pic->registers[register_address];

  new_value = (w_value = cpu16->Wget()) - (src_value = source->get()) -
    (1 - cpu16->status->get_C());

  if(destination)
    source->put(new_value & 0xff);
  else
    cpu16->Wput(new_value & 0xff);

  cpu16->status->put_Z_C_DC_OV_N_for_sub(new_value, w_value, src_value);

  cpu16->pc->increment();

}
