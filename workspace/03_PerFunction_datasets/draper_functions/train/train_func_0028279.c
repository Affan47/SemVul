args_concat(TABDCA *dca)
{
   const char  *arg;
   int          i;
   int          j;
   int          j0;
   int          j1;
   int          len;
   int          lentot;
   int          narg;
   int          nline = 0;
   void        *ret;
   char       **sqllines = NULL;

   narg = mpl_tab_num_args(dca);

   if (narg < 3)
      return NULL;

   for (j = 3; j <= narg; j++)
   {
      arg = mpl_tab_get_arg(dca, j);
      len = strlen(arg);
      if (arg[len-1] == ';' || j == narg)
        nline ++;
   }

   sqllines = (char **) xmalloc((nline+1) * sizeof(char **));

   sqllines[0] = NULL;
   j0     = 3;
   i      = 0;
   lentot = 0;
   for (j = 3; j <= narg; j++)
   {
      arg = mpl_tab_get_arg(dca, j);
      len = strlen(arg);

      lentot += len;


      lentot++;
      if (arg[len-1] == ';' || j == narg)
      {
         sqllines[i] = xmalloc(lentot);
         sqllines[i+1] = NULL;
         sqllines[i][0] = 0x00;
         for (j1 = j0; j1 <= j; j1++)
         {  if(j1>j0)
               strcat(sqllines[i], " ");
            strcat(sqllines[i], mpl_tab_get_arg(dca, j1));
         }
         len = strlen(sqllines[i]);
         if (sqllines[i][len-1] == ';')
            sqllines[i][len-1] = 0x00;
         j0 = j+1;
         i++;
         lentot = 0;
      }
   }
   return sqllines;
}
