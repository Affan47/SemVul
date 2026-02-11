spcg_break_info(const char *funcName, OEM_SP_DATA *data,
			    const char *reason, int iter, int nAuf, int npj,
			    int npc, REAL res2, REAL *ores, WORKSPACE *ws)
{
  REAL  res = sqrt(res2);

  if (*ores  &&  *ores > 0)
  {
    INFO(data->info,2,"%3d | %11.5le | %8.2le |", iter, res, res/(*ores));
  }
  else
  {
    INFO(data->info,2,"%3d | %11.5le |         |", iter);
  }

  if (nAuf >= 0)
  {
    PRINT_INFO(data->info,2," %4d |", nAuf);
  }
  if (npj >= 0)
  {
    PRINT_INFO(data->info,2," %4d |", npj);
  }
  if (npc >= 0)
  {
    PRINT_INFO(data->info,2," ---- |");
  }
  PRINT_INFO(data->info,2,"\n");
  INFO(data->info,2,"stop due to: %s\n", reason);

  data->residual = res;
  if (ws != data->ws)
    FREE_WORKSPACE(ws);
  return;
}
