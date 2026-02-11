lmc_t1_set_circuit_type (lmc_softc_t * const sc, int ie)
{
  if (ie == LMC_CTL_CIRCUIT_TYPE_T1) {
      sc->lmc_miireg16 |= LMC_MII16_T1_Z;
      sc->ictl.circuit_type = LMC_CTL_CIRCUIT_TYPE_T1;
      printk(KERN_INFO "%s: In T1 Mode\n", sc->name);
  }
  else {
      sc->lmc_miireg16 &= ~LMC_MII16_T1_Z;
      sc->ictl.circuit_type = LMC_CTL_CIRCUIT_TYPE_E1;
      printk(KERN_INFO "%s: In E1 Mode\n", sc->name);
  }

  lmc_mii_writereg (sc, 0, 16, sc->lmc_miireg16);

}
