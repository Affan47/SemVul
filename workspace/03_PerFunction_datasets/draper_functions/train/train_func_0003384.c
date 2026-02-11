print_ls_output(char *fname, char *link, int type, struct stat *statp)
{
   char buf[2000];
   char ec1[30];
   char *p, *f;
   int n;

   if (type == FT_LNK) {
      statp->st_mtime = 0;
      statp->st_mode |= 0777;
   }
   p = encode_mode(statp->st_mode, buf);
   n = sprintf(p, " %2d ", (uint32_t)statp->st_nlink);
   p += n;
   n = sprintf(p, "%-4d %-4d", (int)statp->st_uid, (int)statp->st_gid);
   p += n;
   n = sprintf(p, "%10.10s ", edit_uint64(statp->st_size, ec1));
   p += n;
   if (S_ISCHR(statp->st_mode) || S_ISBLK(statp->st_mode)) {
      n = sprintf(p, "%4x ", (int)statp->st_rdev);
   } else {
      n = sprintf(p, "     ");
   }
   p += n;
   p = encode_time(statp->st_mtime, p);
   *p++ = ' ';

   for (f=fname; *f && (p-buf) < (int)sizeof(buf); )
      *p++ = *f++;
   if (type == FT_LNK) {
      *p++ = '-';
      *p++ = '>';
      *p++ = ' ';

      for (f=link; *f && (p-buf) < (int)sizeof(buf); )
         *p++ = *f++;
   }
   *p++ = '\n';
   *p = 0;
   fputs(buf, stdout);
}
