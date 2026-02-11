iv_mult (struct rtx_iv *iv, rtx mby)
{
  enum machine_mode mode = iv->extend_mode;

  if (GET_MODE (mby) != VOIDmode
      && GET_MODE (mby) != mode)
    return false;

  if (iv->extend == IV_UNKNOWN_EXTEND)
    {
      iv->base = simplify_gen_binary (MULT, mode, iv->base, mby);
      iv->step = simplify_gen_binary (MULT, mode, iv->step, mby);
    }
  else
    {
      iv->delta = simplify_gen_binary (MULT, mode, iv->delta, mby);
      iv->mult = simplify_gen_binary (MULT, mode, iv->mult, mby);
    }

  return true;
}
