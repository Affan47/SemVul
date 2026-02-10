lmc_led_off(lmc_softc_t * const sc, u32 led)
{
    lmc_trace(sc->lmc_device, "lmc_led_off in");
    if(sc->lmc_miireg16 & led){
        lmc_trace(sc->lmc_device, "lmc_led_off aoff out");
        return;
    }

    sc->lmc_miireg16 |= led;
    lmc_mii_writereg(sc, 0, 16, sc->lmc_miireg16);
    lmc_trace(sc->lmc_device, "lmc_led_off out");
}
