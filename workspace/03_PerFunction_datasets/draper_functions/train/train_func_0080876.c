uc_set_source_2d( UcDriverData *ucdrv,
                  UcDeviceData *ucdev,
                  CardState    *state )
{
     struct uc_fifo *fifo   = ucdrv->fifo;

     if (UC_IS_VALID( uc_source2d ))
          return;

     ucdev->pitch &= 0x7fff0000;
     ucdev->pitch |= (state->src.pitch >> 3) & 0x7fff;

     UC_FIFO_PREPARE( fifo, 6 );
     UC_FIFO_ADD_HDR( fifo, HC_ParaType_NotTex << 16 );

     UC_FIFO_ADD_2D ( fifo, VIA_REG_SRCBASE, state->src.offset >> 3 );
     UC_FIFO_ADD_2D ( fifo, VIA_REG_PITCH,   VIA_PITCH_ENABLE | ucdev->pitch );

     UC_FIFO_CHECK( fifo );

     ucdev->src_offset = state->src.offset;
     ucdev->src_pitch = state->src.pitch;
     ucdev->src_height = state->source->config.size.h;

     UC_VALIDATE( uc_source2d );
}
