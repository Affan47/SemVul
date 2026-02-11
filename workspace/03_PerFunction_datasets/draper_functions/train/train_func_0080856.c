glp_write_mip(glp_prob *mip, const char *fname)
{     XFILE *fp;
      int i, j, ret = 0;
      xprintf("Writing MIP solution to `%s'...\n", fname);
      fp = xfopen(fname, "w");
      if (fp == NULL)
      {  xprintf("Unable to create `%s' - %s\n", fname, xerrmsg());
         ret = 1;
         goto done;
      }

      xfprintf(fp, "%d %d\n", mip->m, mip->n);

      xfprintf(fp, "%d %.*g\n", mip->mip_stat, DBL_DIG, mip->mip_obj);

      for (i = 1; i <= mip->m; i++)
         xfprintf(fp, "%.*g\n", DBL_DIG, mip->row[i]->mipx);

      for (j = 1; j <= mip->n; j++)
         xfprintf(fp, "%.*g\n", DBL_DIG, mip->col[j]->mipx);
      xfflush(fp);
      if (xferror(fp))
      {  xprintf("Write error on `%s' - %s\n", fname, xerrmsg());
         ret = 1;
         goto done;
      }
      xprintf("%d lines were written\n", 2 + mip->m + mip->n);
done: if (fp != NULL) xfclose(fp);
      return ret;
}
