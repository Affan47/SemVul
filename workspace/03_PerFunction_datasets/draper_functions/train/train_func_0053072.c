r200_set_drawingflags( RadeonDriverData *rdrv,
                            RadeonDeviceData *rdev,
                            CardState        *state )
{
     volatile u8   *mmio        = rdrv->mmio_base;
     u32            master_cntl = rdev->gui_master_cntl       |
                                  GMC_SRC_DATATYPE_MONO_FG_LA |
                                  GMC_BRUSH_SOLID_COLOR       |
                                  GMC_CLR_CMP_CNTL_DIS;
     u32            rb3d_cntl   = rdev->rb3d_cntl & ~DITHER_ENABLE;
     u32            pp_cntl     = TEX_BLEND_1_ENABLE;
     u32            cblend      = R200_TXC_ARG_C_TFACTOR_COLOR;

     if (RADEON_IS_SET( DRAWING_FLAGS ))
          return;

     if (rdev->dst_422) {
          pp_cntl |= TEX_1_ENABLE;
          cblend   = R200_TXC_ARG_C_R1_COLOR;
     }
     else if (rdev->dst_format == DSPF_A8) {
          cblend = R200_TXC_ARG_C_TFACTOR_ALPHA;
     }

     if (state->drawingflags & DSDRAW_BLEND)
          rb3d_cntl |= ALPHA_BLEND_ENABLE;

     if (state->drawingflags & DSDRAW_XOR) {
          rb3d_cntl   |= ROP_ENABLE;
          master_cntl |= GMC_ROP3_PATXOR;
     }
     else {
          master_cntl |= GMC_ROP3_PATCOPY;
     }

     if (state->render_options & DSRO_ANTIALIAS)
          pp_cntl |= ANTI_ALIAS_LINE_POLY;

     radeon_waitfifo( rdrv, rdev, 11 );
     radeon_out32( mmio, DP_GUI_MASTER_CNTL, master_cntl );
     radeon_out32( mmio, DP_CNTL, DST_X_LEFT_TO_RIGHT | DST_Y_TOP_TO_BOTTOM );
     radeon_out32( mmio, RB3D_CNTL, rb3d_cntl );
     radeon_out32( mmio, SE_CNTL, DIFFUSE_SHADE_FLAT  |
                                  ALPHA_SHADE_FLAT    |
                                  BFACE_SOLID         |
                                  FFACE_SOLID         |
                                  VTX_PIX_CENTER_OGL  |
                                  ROUND_MODE_ROUND    |
				              ROUND_PREC_4TH_PIX );
     radeon_out32( mmio, PP_CNTL, pp_cntl );
     radeon_out32( mmio, R200_PP_TXCBLEND_1, cblend );
     radeon_out32( mmio, R200_PP_TXCBLEND2_1, (1 << R200_TXC_TFACTOR_SEL_SHIFT) |
                                              R200_TXC_OUTPUT_REG_R0            |
                                              R200_TXC_CLAMP_0_1 );
     radeon_out32( mmio, R200_PP_TXABLEND_1, R200_TXA_ARG_C_TFACTOR_ALPHA );
     radeon_out32( mmio, R200_PP_TXABLEND2_1, (1 << R200_TXA_TFACTOR_SEL_SHIFT) |
                                              R200_TXA_OUTPUT_REG_R0            |
                                              R200_TXA_CLAMP_0_1 );
     radeon_out32( mmio, R200_SE_VTX_FMT_0, R200_VTX_XY );
     radeon_out32( mmio, R200_SE_VTX_FMT_1, 0 );

     rdev->drawingflags = state->drawingflags;

     RADEON_SET  ( DRAWING_FLAGS );
     RADEON_UNSET( BLITTING_FLAGS );
}
