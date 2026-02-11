mark_temp_addr_taken (x)
     rtx x;
{
  struct temp_slot *p;

  if (x == 0)
    return;


  if (GET_CODE (x) != MEM || CONSTANT_P (XEXP (x, 0)))
    return;

  p = find_temp_slot_from_address (XEXP (x, 0));
  if (p != 0)
    p->addr_taken = 1;
}
