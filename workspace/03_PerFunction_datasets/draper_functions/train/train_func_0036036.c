lmc_ssi_set_crc_length (lmc_softc_t * const sc, int state)
{
  if (state == LMC_CTL_CRC_LENGTH_32)
    {

      sc->lmc_miireg16 |= LMC_MII16_SSI_CRC;
      sc->ictl.crc_length = LMC_CTL_CRC_LENGTH_32;
      sc->lmc_crcSize = LMC_CTL_CRC_BYTESIZE_4;

    }
  else
    {

      sc->lmc_miireg16 &= ~LMC_MII16_SSI_CRC;
      sc->ictl.crc_length = LMC_CTL_CRC_LENGTH_16;
      sc->lmc_crcSize = LMC_CTL_CRC_BYTESIZE_2;
    }

  lmc_mii_writereg (sc, 0, 16, sc->lmc_miireg16);
}
