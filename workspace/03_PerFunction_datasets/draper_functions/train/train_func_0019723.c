validize_mem (rtx ref)
{
  if (GET_CODE (ref) != MEM)
    return ref;
  if (! (flag_force_addr && CONSTANT_ADDRESS_P (XEXP (ref, 0)))
      && memory_address_p (GET_MODE (ref), XEXP (ref, 0)))
    return ref;


  return replace_equiv_address (ref, XEXP (ref, 0));
}
