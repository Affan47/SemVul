bng_generic_sub
       (bng a, bngsize alen,
        bng b, bngsize blen,
        bngcarry carry)
{
  alen -= blen;
  for (; blen > 0; blen--, a++, b++) {
    BngSub2Carry(*a, carry, *a, *b, carry);
  }
  if (carry == 0 || alen == 0) return carry;
  do {
    if ((*a)-- != 0) return 0;
    a++;
  } while (--alen);
  return 1;
}
