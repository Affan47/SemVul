rlim_to_I (rlim_t lim)
{ return lim == RLIM_INFINITY ? NIL : rlim_to_I_0(lim); }
