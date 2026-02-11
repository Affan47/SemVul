vt_getcpu_read(uint32_t* value, uint8_t* changed)
{
  int cpuid;
  *changed = 0;

  if ( (cpuid = sched_getcpu()) == -1 )
    vt_error_msg("sched_getcpu: %s", strerror(errno));

  if( (uint32_t)cpuid != *value )
  {
    *value = (uint32_t)cpuid;
    *changed = 1;
  }
}
