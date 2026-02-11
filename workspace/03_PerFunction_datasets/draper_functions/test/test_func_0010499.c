gl847_homsnr_gpio(Genesys_Device *dev)
{
uint8_t val;
SANE_Status status=SANE_STATUS_GOOD;

  if (dev->model->gpo_type == GPO_CANONLIDE700)
    {
      RIE (sanei_genesys_read_register (dev, REG6C, &val));
      val &= ~REG6C_GPIO10;
      RIE (sanei_genesys_write_register (dev, REG6C, val));
    }
  else
    {
      RIE (sanei_genesys_read_register (dev, REG6C, &val));
      val |= REG6C_GPIO10;
      RIE (sanei_genesys_write_register (dev, REG6C, val));
    }
  return status;
}
