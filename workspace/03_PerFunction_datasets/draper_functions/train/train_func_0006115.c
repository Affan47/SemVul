break_info(const char *funcName, OEM_DATA *oem, const char *reason,
		int iter, REAL res, REAL *ores, WORKSPACE *ws)
{
  if (*ores  &&  *ores > 0)
    INFO(oem->info,2,"%5d | %12.5le | %8.2le\n", iter, res, res/(*ores));
  else
    INFO(oem->info,2,"%5d | %12.5le |\n", iter);
  INFO(oem->info,2,"stop due to: %s\n", reason);

  free_oem_workspace(ws, oem);
  oem->residual = res;
}
