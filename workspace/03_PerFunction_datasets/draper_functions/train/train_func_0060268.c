lmc_set_protocol (lmc_softc_t * const sc, lmc_ctl_t * ctl)
{
	if (!ctl)
		sc->ictl.keepalive_onoff = LMC_CTL_ON;
}
