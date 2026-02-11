tdfx_validate_destination3D( TDFXDriverData *tdrv,
                                                TDFXDeviceData *tdev,
                                                CardState      *state )
{
     CoreSurface   *destination = state->destination;
     Voodoo3D      *voodoo3D    = tdrv->voodoo3D;

     u32 lfbmode = TDFX_LFBMODE_PIXEL_PIPELINE_ENABLE;
     u32 fbzMode = (1 << 9) | 1;

     if (tdev->v_destination3D)
          return;

     switch (destination->config.format) {
          case DSPF_ARGB1555:
               lfbmode |= TDFX_LFBMODE_RGB555;
               break;
          case DSPF_RGB16:
               lfbmode |= TDFX_LFBMODE_RGB565;
               break;
          case DSPF_RGB32:
               lfbmode |= TDFX_LFBMODE_RGB0888;
               break;
          case DSPF_ARGB:
               fbzMode |= (1 << 10);
               lfbmode |= TDFX_LFBMODE_ARGB8888;
               break;
          default:
               D_BUG( "unexpected pixelformat!" );
               break;
     }

     tdfx_waitfifo( tdrv, tdev, 4 );

     voodoo3D->lfbMode = lfbmode;
     voodoo3D->fbzMode = fbzMode;
     voodoo3D->colBufferAddr = state->dst.offset;
     voodoo3D->colBufferStride = state->dst.pitch;

     tdev->v_destination3D = 1;
}
