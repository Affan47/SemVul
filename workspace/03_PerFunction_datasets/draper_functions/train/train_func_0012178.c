lcdInit(void) {
    int id;

    sspInit(0, sspClockPolarity_Low, sspClockPhase_RisingEdge);

    gpioSetValue(RB_LCD_CS, 1);
    gpioSetValue(RB_LCD_RST, 1);

    gpioSetDir(RB_LCD_CS, gpioDirection_Output);
    gpioSetDir(RB_LCD_RST, gpioDirection_Output);

    delayms(100);
    gpioSetValue(RB_LCD_RST, 0);
    delayms(100);
    gpioSetValue(RB_LCD_RST, 1);
    delayms(100);

    id=lcdRead(220);

    if(id==14)
        displayType=DISPLAY_N1600;
    else
        displayType=DISPLAY_N1200;


    lcd_select();

    if(displayType==DISPLAY_N1200){
        uint8_t initseq[]= { 0xE2,0xAF,
                             0xA1,
                             0xA4, 0x2F, 0xB0, 0x10};
        int i = 0;
        while(i<sizeof(initseq)){
            lcdWrite(TYPE_CMD,initseq[i++]);
            delayms(5);
        }
    }else{
        uint8_t initseq_d[] = {
                               0x36,
                               0x29, 0xBA, 0x07,
                               0x15, 0x25, 0x3f,
                               0x11, 0x13, 0x37,
                               0x00, 0x3A, 0x05,
                               0x2A, 0, 98-1,
                               0x2B, 0, 70-1};
        uint32_t initseq_c = ~ 0x12BA7;
        int i = 0;
        lcdWrite(TYPE_CMD,0x01);
        delayms(10);

        while(i<sizeof(initseq_d)){
            lcdWrite(initseq_c&1, initseq_d[i++]);
            initseq_c = initseq_c >> 1;
        }
    }
    lcd_deselect();
}
