Bop_NV_to_Aop( GenefxState *gfxs )
{
     direct_memmove( gfxs->Aop[0], gfxs->Bop[0], gfxs->length );
     if (gfxs->dst_format == DSPF_NV16 || gfxs->AopY & 1)
          direct_memmove( gfxs->Aop[1], gfxs->Bop[1], gfxs->length&~1 );
}
