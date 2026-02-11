r300_set_blend_function( RadeonDriverData *rdrv,
                         RadeonDeviceData *rdev,
                         CardState        *state )
{
     u32 sblend, dblend;

     if (RADEON_IS_SET( SRC_BLEND ) && RADEON_IS_SET( DST_BLEND ))
          return;

     sblend = r300SrcBlend[state->src_blend-1];
     dblend = r300DstBlend[state->dst_blend-1];

     if (!DFB_PIXELFORMAT_HAS_ALPHA(rdev->dst_format)) {
          if (sblend == SRC_BLEND_GL_DST_ALPHA)
               sblend = SRC_BLEND_GL_ONE;
          else if (sblend == SRC_BLEND_GL_ONE_MINUS_DST_ALPHA)
               sblend = SRC_BLEND_GL_ZERO;

          if (dblend == DST_BLEND_GL_DST_ALPHA)
               dblend = DST_BLEND_GL_ONE;
          else if (dblend == DST_BLEND_GL_ONE_MINUS_DST_ALPHA)
               dblend = DST_BLEND_GL_ZERO;
     }

     rdev->rb3d_blend = sblend | dblend;

     RADEON_UNSET( DRAWING_FLAGS );
     RADEON_UNSET( BLITTING_FLAGS );
     RADEON_SET( SRC_BLEND );
     RADEON_SET( DST_BLEND );
}
