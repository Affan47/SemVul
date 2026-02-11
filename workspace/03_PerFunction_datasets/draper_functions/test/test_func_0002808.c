save_state()
{

  if(!rom || !rom_size)
    return;

  for (unsigned int i = 0; i < rom_size; i++)
    if(rom[i])
      rom[i]->put_trace_state(rom[i]->value);

}
