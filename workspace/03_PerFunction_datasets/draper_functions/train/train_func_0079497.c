dbf_close_file(TABDCA *dca, struct dbf *dbf)
{
      int ret = 0;
      xassert(dca == dca);
      if (dbf->mode == 'W')
      {  if (setjmp(dbf->jump))
         {  ret = 1;
            goto skip;
         }

         write_byte(dbf, 0x1A);

         dbf->offset = 4;
         if (fseek(dbf->fp, dbf->offset, SEEK_SET))
         {  xprintf("%s:0x%X: seek error - %s\n", dbf->fname,
               dbf->offset, strerror(errno));
            longjmp(dbf->jump, 0);
         }
         write_byte(dbf, dbf->count);
         write_byte(dbf, dbf->count >> 8);
         write_byte(dbf, dbf->count >> 16);
         write_byte(dbf, dbf->count >> 24);
         fflush(dbf->fp);
         if (ferror(dbf->fp))
         {  xprintf("%s:0x%X: write error - %s\n", dbf->fname,
               dbf->offset, strerror(errno));
            longjmp(dbf->jump, 0);
         }
skip:    ;
      }
      xfree(dbf->fname);
      fclose(dbf->fp);
      xfree(dbf);
      return ret;
}
