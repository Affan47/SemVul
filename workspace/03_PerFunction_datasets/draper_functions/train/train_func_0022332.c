uc_set_clip( UcDriverData *ucdrv,
             UcDeviceData *ucdev,
             CardState    *state )
{
     struct uc_fifo *fifo = ucdrv->fifo;

     if (DFB_REGION_EQUAL( ucdev->clip, state->clip ))
          return;

     UC_FIFO_PREPARE( fifo, 8 );
     UC_FIFO_ADD_HDR( fifo, HC_ParaType_NotTex << 16 );

#ifdef UC_ENABLE_3D

     UC_FIFO_ADD_3D ( fifo, HC_SubA_HClipTB,
                      (RS12(state->clip.y1) << 12) | RS12(state->clip.y2+1) );
     UC_FIFO_ADD_3D ( fifo, HC_SubA_HClipLR,
                      (RS12(state->clip.x1) << 12) | RS12(state->clip.x2+1) );

#endif

     UC_FIFO_ADD_2D ( fifo, VIA_REG_CLIPTL,
                      (RS16(state->clip.y1) << 16) | RS16(state->clip.x1) );
     UC_FIFO_ADD_2D ( fifo, VIA_REG_CLIPBR,
                      (RS16(state->clip.y2) << 16) | RS16(state->clip.x2) );

     UC_FIFO_CHECK( fifo );

     ucdev->clip = state->clip;
}
