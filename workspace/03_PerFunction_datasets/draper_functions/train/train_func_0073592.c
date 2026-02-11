__exec_history_list(int32 num)
{
 register int32 i;
 int32 h_start, nlines;
 char s1[RECLEN];

 if (num == 0) h_start = 1;
 else { if ((h_start = __iah_lasti - num + 1) <= 1) h_start = 1; }
 for (nlines = 0, i = h_start; i <= __iah_lasti; i++)
  {
   nlines += prt1_iahist_cmd(i);
   if (nlines > __hist_cur_listnum)
    {
     nlines = 0;
     __cvsim2_msg("Press return to continue:");
     fgets(s1, RECLEN, stdin);
    }
  }
}
