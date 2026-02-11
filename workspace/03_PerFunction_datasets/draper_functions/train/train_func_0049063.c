Cop_to_Aop_32( GenefxState *gfxs )
{
     int    w   = gfxs->length;
     u32   *D   = gfxs->Aop[0];
     u32    Cop = gfxs->Cop;

     while (w--)
          *D++ = Cop;
}
