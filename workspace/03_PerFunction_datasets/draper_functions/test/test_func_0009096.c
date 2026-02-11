genie_shorten_long_mp_to_real (NODE_T * p)
{
  MOID_T *mode = LHS_MODE (p);
  int digits = get_mp_digits (mode), size = get_mp_size (mode);
  MP_T *z;
  DECREMENT_STACK_POINTER (p, size);
  z = (MP_T *) STACK_TOP;
  MP_STATUS (z) = (MP_T) INIT_MASK;
  PUSH_PRIMITIVE (p, mp_to_real (p, z, digits), A68_REAL);
}
