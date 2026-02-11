dbf_read_record(TABDCA *dca, struct dbf *dbf)
{
      int b, j, k, ret = 0;
      char buf[DBF_FDLEN_MAX+1];
      xassert(dbf->mode == 'R');
      if (setjmp(dbf->jump))
      {  ret = 1;
         goto done;
      }

      b = read_byte(dbf);
      if (b == 0x1A)
      {
         ret = -1;
         goto done;
      }
      if (b != 0x20)
      {  xprintf("%s:0x%X: invalid record flag\n", dbf->fname,
            dbf->offset);
         longjmp(dbf->jump, 0);
      }

      if (dbf->ref[0] > 0)
         mpl_tab_set_num(dca, dbf->ref[0], dbf->count+1);

      for (k = 1; k <= dbf->nf; k++)
      {
         for (j = 0; j < dbf->len[k]; j++)
            buf[j] = (char)read_byte(dbf);
         buf[dbf->len[k]] = '\0';

         if (dbf->type[k] == 'C')
         {
            if (dbf->ref[k] > 0)
               mpl_tab_set_str(dca, dbf->ref[k], strtrim(buf));
         }
         else if (dbf->type[k] == 'N')
         {
            if (dbf->ref[k] > 0)
            {  double num;
               strspx(buf);
               xassert(str2num(buf, &num) == 0);
               mpl_tab_set_num(dca, dbf->ref[k], num);
            }
         }
         else
            xassert(dbf != dbf);
      }

      dbf->count++;
done: return ret;
}
