startBackupFile(bpContext *ctx, struct save_pkt *sp)
{
   delta_test *self = get_self(ctx);
   if (!self) {
      return bRC_Error;
   }
   time_t now = time(NULL);
   sp->fname = (char *)"/delta.txt";
   sp->type = FT_REG;
   sp->statp.st_mode = 0700 | S_IFREG;
   sp->statp.st_ctime = now;
   sp->statp.st_mtime = now;
   sp->statp.st_atime = now;
   sp->statp.st_size = -1;
   sp->statp.st_blksize = 4096;
   sp->statp.st_blocks = 1;
   if (self->level == 'I' || self->level == 'D') {
      bRC state = bfuncs->checkChanges(ctx, sp);

      sp->type = (state == bRC_Seen)? FT_NOCHG : FT_REG;
      sp->flags |= (FO_DELTA|FO_OFFSETS);
      self->delta = sp->delta_seq + 1;
   }
   pm_strcpy(self->fname, files[self->delta % nb_files]);
   Dmsg(ctx, dbglvl, "delta-test-fd: delta_seq=%i delta=%i fname=%s\n",
        sp->delta_seq, self->delta, self->fname);

   return bRC_OK;
}
