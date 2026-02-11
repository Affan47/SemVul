bng_generic_sub_carry
       (bng a,  bngsize alen, bngcarry carry)
{
  if (carry == 0 || alen == 0) return carry;
  do {
    if ((*a)-- != 0) return 0;
    a++;
  } while (--alen);
  return 1;
}
