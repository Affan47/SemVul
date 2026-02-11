ZZX_maxlimbs(const ZZX& z)
{
   unsigned long length = deg(z)+1;
   unsigned long maxlimbs = 0;
   unsigned long newlimbs, i;
   const ZZ *ap;

   if (length == 0) return 0;

   for (i = 0, ap = z.rep.elts(); i < length; ap++, i++)
   {
      newlimbs = ZZ_limbs(*ap);
      if (newlimbs > maxlimbs) maxlimbs = newlimbs;
   }
   return maxlimbs;
}
