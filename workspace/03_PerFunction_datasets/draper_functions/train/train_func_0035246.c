spcg_solve_info(const char *funcName, OEM_SP_DATA *data, int iter,
			   int nAuf, int npj, int npc, REAL res2, REAL *ores,
			   WORKSPACE *ws)
{
  static int  step[7] = {0, 0, 10, 5, 2, 1, 1};
  REAL  res = sqrt(res2);

  if (res <= data->tolerance || ((data->info>1) && (iter%step[data->info]== 0))
      || iter == data->max_iter)
  {
    if (ores)
    {
     if (*ores > 0.0)
      {
	REAL  red = res/(*ores);
	INFO(data->info,2,"%3d | %11.5le | %8.2le |", iter, res, red);
      }
      else
      {
	INFO(data->info,2,"%3d | %11.5le | -------- |", iter, res);
      }
      *ores = res;
    }
    else
    {
      INFO(data->info,2,"%2d | %11.5le |", iter, res);
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
      PRINT_INFO(data->info,2," %4d |", npc);
    }
    PRINT_INFO(data->info,2,"\n");
  }

  data->residual = res;

  if (iter == data->max_iter && res > data->tolerance)
  {
    INFO(data->info,1,"tolerance %le not reached after %d iterations\n",
		      data->tolerance, iter);
    if (ws != data->ws) FREE_WORKSPACE(ws);
    return(1);
  }

  if (res <= data->tolerance)
  {
    INFO(data->info,6,"finished successfully with %d iterations\n",iter);
    if (ws != data->ws) FREE_WORKSPACE(ws);
    return(1);
  }

  return(0);
}
