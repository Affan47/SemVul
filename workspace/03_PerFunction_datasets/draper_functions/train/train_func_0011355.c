set_PC(unsigned int new_pc)
{
  if(cpu && cpu->pc)
    return cpu->pc->put_value(new_pc);
}
