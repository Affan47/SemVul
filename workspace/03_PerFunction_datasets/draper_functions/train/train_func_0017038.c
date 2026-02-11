nsf_setchan (nsf_t * nsf, int chan, boolean enabled)
{
  if (!nsf)
    return -1;

  nsf_setcontext (nsf);
  return apu_setchan (chan, enabled);
}
