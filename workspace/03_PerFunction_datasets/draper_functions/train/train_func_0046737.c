StartScan ()
{
  DBG (DBG_FUNC, "StartScan: start\n");
  if (ST_Reflective == g_ScanType)
    {
      DBG (DBG_INFO, "StartScan: g_ScanType==ST_Reflective\n");

      return Reflective_SetupScan (g_ssSuggest.cmScanMode,
				   g_ssSuggest.wXDpi,
				   g_ssSuggest.wYDpi,
				   PF_BlackIs0,
				   g_ssSuggest.wX,
				   g_ssSuggest.wY,
				   g_ssSuggest.wWidth, g_ssSuggest.wHeight);
    }
  else

    {

      DBG (DBG_INFO, "StartScan: g_ScanType==ST_Transparent\n");

      return Transparent_SetupScan (g_ssSuggest.cmScanMode,
				    g_ssSuggest.wXDpi,
				    g_ssSuggest.wYDpi,
				    PF_BlackIs0,
				    g_ssSuggest.wX,
				    g_ssSuggest.wY,
				    g_ssSuggest.wWidth, g_ssSuggest.wHeight);
    }
}
