__lbitxor(word32 *op1ap, word32 *op1bp, word32 *op2ap, word32 *op2bp,
 int32 opbits)
{
 register int32 wi;
 int32 wlen;

 wlen = wlen_(opbits);
 for (wi = 0; wi < wlen; wi++)
  {
   if ((op1bp[wi] | op2bp[wi]) == 0L)
    { op1bp[wi] = 0L; op1ap[wi] = op1ap[wi] ^ op2ap[wi]; }
   else
    {
     op1bp[wi] = op1bp[wi] | op2bp[wi];
     op1ap[wi] = op1bp[wi] | (op1ap[wi] ^ op2ap[wi]);
    }
  }

}
