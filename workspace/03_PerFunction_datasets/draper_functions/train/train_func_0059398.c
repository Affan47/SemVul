calc_load(struct Client *sptr, const struct StatDesc *sd, char *param)
{

  static const char *header =

      "Minute  Hour    Day   Yest. YYest. Userload for:";

  static const char *what[3] = {
    "local clients",
    "total clients",
    "total connections"
  };
  int i, j, times[5][3];

  int last_m_index = m_index, last_h_index = h_index;

  update_load();

  if (--last_m_index < 0)
    last_m_index = 59;
  times[0][0] = (cspm[last_m_index].local_count + 3) / 6;
  times[0][1] = (cspm[last_m_index].client_count + 3) / 6;
  times[0][2] = (cspm[last_m_index].conn_count + 3) / 6;

  times[1][0] = (csph_sum.local_count + 180) / 360;
  times[1][1] = (csph_sum.client_count + 180) / 360;
  times[1][2] = (csph_sum.conn_count + 180) / 360;

  for (i = 2; i < 5; ++i)
  {
    times[i][0] = 43200;
    times[i][1] = 43200;
    times[i][2] = 43200;
    for (j = 0; j < 24; ++j)
    {
      if (--last_h_index < 0)
        last_h_index = 71;
      times[i][0] += csph[last_h_index].local_count;
      times[i][1] += csph[last_h_index].client_count;
      times[i][2] += csph[last_h_index].conn_count;
    }
    times[i][0] /= 86400;
    times[i][1] /= 86400;
    times[i][2] /= 86400;
  }

  sendcmdto_one(&me, CMD_NOTICE, sptr, "%C :%s", sptr, header);
  for (i = 0; i < 3; ++i)
    sendcmdto_one(&me, CMD_NOTICE, sptr,
		  "%C :%4d.%1d  %4d.%1d  %4d  %4d  %4d   %s", sptr,
		  times[0][i] / 10, times[0][i] % 10,
		  times[1][i] / 10, times[1][i] % 10,
		  times[2][i], times[3][i], times[4][i], what[i]);
}
