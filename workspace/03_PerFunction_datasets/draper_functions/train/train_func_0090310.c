display(struct csa *csa, const glp_smcp *parm, int spec)
{     int m = csa->m;
      int n = csa->n;
      double *coef = csa->coef;
      char *orig_type = csa->orig_type;
      int *head = csa->head;
      char *stat = csa->stat;
      int phase = csa->phase;
      double *bbar = csa->bbar;
      double *cbar = csa->cbar;
      int i, j, cnt;
      double sum;
      if (parm->msg_lev < GLP_MSG_ON) goto skip;
      if (parm->out_dly > 0 &&
         1000.0 * xdifftime(xtime(), csa->tm_beg) < parm->out_dly)
         goto skip;
      if (csa->it_cnt == csa->it_dpy) goto skip;
      if (!spec && csa->it_cnt % parm->out_frq != 0) goto skip;

      sum = 0.0;
      if (phase == 1)
      {  for (i = 1; i <= m; i++)
            sum -= coef[head[i]] * bbar[i];
         for (j = 1; j <= n; j++)
            sum -= coef[head[m+j]] * get_xN(csa, j);
      }
      else
      {  for (j = 1; j <= n; j++)
         {  if (cbar[j] < 0.0)
               if (stat[j] == GLP_NL || stat[j] == GLP_NF)
                  sum -= cbar[j];
            if (cbar[j] > 0.0)
               if (stat[j] == GLP_NU || stat[j] == GLP_NF)
                  sum += cbar[j];
         }
      }

      cnt = 0;
      for (i = 1; i <= m; i++)
         if (orig_type[head[i]] == GLP_FX) cnt++;
      if (csa->phase == 1)
         xprintf(" %6d: %24s infeas = %10.3e (%d)\n",
            csa->it_cnt, "", sum, cnt);
      else
         xprintf("|%6d: obj = %17.9e  infeas = %10.3e (%d)\n",
            csa->it_cnt, eval_obj(csa), sum, cnt);
      csa->it_dpy = csa->it_cnt;
skip: return;
}
