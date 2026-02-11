IsTAConnected ()
{
  SANE_Bool hasTA;

  DBG (DBG_FUNC, "StopScan: start\n");

  if (Asic_Open (&g_chip, g_pDeviceFile) != STATUS_GOOD)
    {
      return FALSE;
    }

  if (Asic_IsTAConnected (&g_chip, &hasTA) != STATUS_GOOD)
    {
      Asic_Close (&g_chip);
      return FALSE;
    }

  Asic_Close (&g_chip);

  DBG (DBG_FUNC, "StopScan: exit\n");
  return hasTA;
}
