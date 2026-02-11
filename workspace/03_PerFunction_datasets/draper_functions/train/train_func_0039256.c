ov0_set_regs( ATI128DriverData *adrv, ATIOverlayLayerData *aov0 )
{
     volatile u8 *mmio = adrv->mmio_base;

     ati128_out32( mmio, OV0_REG_LOAD_CNTL, 1 );
     while (!(ati128_in32( mmio, OV0_REG_LOAD_CNTL ) & (1 << 3)));

     ati128_out32( mmio, OV0_H_INC,
                   aov0->regs.H_INC );

     ati128_out32( mmio, OV0_STEP_BY,
                   aov0->regs.STEP_BY );

     ati128_out32( mmio, OV0_Y_X_START,
                   aov0->regs.Y_X_START );

     ati128_out32( mmio, OV0_Y_X_END,
                   aov0->regs.Y_X_END );

     ati128_out32( mmio, OV0_V_INC,
                   aov0->regs.V_INC );

     ati128_out32( mmio, OV0_P1_BLANK_LINES_AT_TOP,
                   aov0->regs.P1_BLANK_LINES_AT_TOP );

     ati128_out32( mmio, OV0_P23_BLANK_LINES_AT_TOP,
                   aov0->regs.P23_BLANK_LINES_AT_TOP );

     ati128_out32( mmio, OV0_VID_BUF_PITCH0_VALUE,
                   aov0->regs.VID_BUF_PITCH0_VALUE );

     ati128_out32( mmio, OV0_VID_BUF_PITCH1_VALUE,
                   aov0->regs.VID_BUF_PITCH1_VALUE );

     ati128_out32( mmio, OV0_P1_X_START_END,
                   aov0->regs.P1_X_START_END );

     ati128_out32( mmio, OV0_P2_X_START_END,
                   aov0->regs.P2_X_START_END );

     ati128_out32( mmio, OV0_P3_X_START_END,
                   aov0->regs.P3_X_START_END );

     ati128_out32( mmio, OV0_VID_BUF0_BASE_ADRS,
                   aov0->regs.VID_BUF0_BASE_ADRS );

     ati128_out32( mmio, OV0_VID_BUF1_BASE_ADRS,
                   aov0->regs.VID_BUF1_BASE_ADRS );

     ati128_out32( mmio, OV0_VID_BUF2_BASE_ADRS,
                   aov0->regs.VID_BUF2_BASE_ADRS );

     ati128_out32( mmio, OV0_P1_V_ACCUM_INIT,
                   aov0->regs.P1_V_ACCUM_INIT );

     ati128_out32( mmio, OV0_P23_V_ACCUM_INIT,
                   aov0->regs.P23_V_ACCUM_INIT );

     ati128_out32( mmio, OV0_P1_H_ACCUM_INIT,
                   aov0->regs.P1_H_ACCUM_INIT );

     ati128_out32( mmio, OV0_P23_H_ACCUM_INIT,
                   aov0->regs.P23_H_ACCUM_INIT );

     ati128_out32( mmio, OV0_SCALE_CNTL,
                   aov0->regs.SCALE_CNTL );

     ati128_out32( mmio, OV0_REG_LOAD_CNTL, 0 );
}
