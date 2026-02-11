Bop_argb_blend_alphachannel_one_invsrc_Aop_argb( GenefxState *gfxs )
{
     int  w = gfxs->length;
     u32 *S = gfxs->Bop[0];
     u32 *D = gfxs->Aop[0];

     SET_PIXEL_DUFFS_DEVICE( D, S, w );
}
