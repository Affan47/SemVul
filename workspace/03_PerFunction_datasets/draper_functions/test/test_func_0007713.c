lmc_ds3_get_link_status (lmc_softc_t * const sc)
{
    u16 link_status, link_status_11;
    int ret = 1;

    lmc_mii_writereg (sc, 0, 17, 7);
    link_status = lmc_mii_readreg (sc, 0, 18);


    lmc_led_on(sc, LMC_DS3_LED2);

    if ((link_status & LMC_FRAMER_REG0_DLOS) ||
        (link_status & LMC_FRAMER_REG0_OOFS)){
        ret = 0;
        if(sc->last_led_err[3] != 1){
	    u16 r1;
            lmc_mii_writereg (sc, 0, 17, 01);
            r1 = lmc_mii_readreg (sc, 0, 18);
            r1 &= 0xfe;
            lmc_mii_writereg(sc, 0, 18, r1);
            printk(KERN_WARNING "%s: Red Alarm - Loss of Signal or Loss of Framing\n", sc->name);
        }
        lmc_led_on(sc, LMC_DS3_LED3);
        sc->last_led_err[3] = 1;
    }
    else {
        lmc_led_off(sc, LMC_DS3_LED3);
        if(sc->last_led_err[3] == 1){
	    u16 r1;
            lmc_mii_writereg (sc, 0, 17, 01);
            r1 = lmc_mii_readreg (sc, 0, 18);
            r1 |= 0x01;
            lmc_mii_writereg(sc, 0, 18, r1);
        }
        sc->last_led_err[3] = 0;
    }

    lmc_mii_writereg(sc, 0, 17, 0x10);
    link_status_11 = lmc_mii_readreg(sc, 0, 18);
    if((link_status & LMC_FRAMER_REG0_AIS) ||
       (link_status_11 & LMC_FRAMER_REG10_XBIT)) {
        ret = 0;
        if(sc->last_led_err[0] != 1){
            printk(KERN_WARNING "%s: AIS Alarm or XBit Error\n", sc->name);
            printk(KERN_WARNING "%s: Remote end has loss of signal or framing\n", sc->name);
        }
        lmc_led_on(sc, LMC_DS3_LED0);
        sc->last_led_err[0] = 1;
    }
    else {
        lmc_led_off(sc, LMC_DS3_LED0);
        sc->last_led_err[0] = 0;
    }

    lmc_mii_writereg (sc, 0, 17, 9);
    link_status = lmc_mii_readreg (sc, 0, 18);

    if(link_status & LMC_FRAMER_REG9_RBLUE){
        ret = 0;
        if(sc->last_led_err[1] != 1){
            printk(KERN_WARNING "%s: Blue Alarm - Receiving all 1's\n", sc->name);
        }
        lmc_led_on(sc, LMC_DS3_LED1);
        sc->last_led_err[1] = 1;
    }
    else {
        lmc_led_off(sc, LMC_DS3_LED1);
        sc->last_led_err[1] = 0;
    }

    return ret;
}
