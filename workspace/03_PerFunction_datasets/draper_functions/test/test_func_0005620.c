opcode_loadb(void)
{
  uint8_t *address = z_mem + (uint16_t)(op[0] + (int16_t)op[1]);

  TRACE_LOG("Opcode: LOADB.\n");

  read_z_result_variable();

  if (address > active_z_story->static_memory_end)
  {
    TRACE_LOG("Static memory end: %x.\n", active_z_story->static_memory_end);
    TRACE_LOG("Trying to loadb from %x which is above static memory.\n",
        address);
    set_variable(z_res_var, 0, false);
  }
  else
  {
    TRACE_LOG("Loading from %x to var %x.\n",
        *address,
        z_res_var);
    set_variable(z_res_var, *address, false);
  }
}
