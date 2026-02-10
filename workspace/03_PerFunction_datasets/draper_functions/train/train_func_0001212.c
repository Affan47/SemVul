f_seek(File *f, long pos)
{
#ifdef FBUF
   if (f->size > 0)
     {
        if (pos >= f->size) pos = f->size -1;
     }
#endif
   if (f->pos == pos) return;
   f->pos = pos;
#ifdef FBUF
   _f_read_pos(f, f->pos, 1);
#else
   gzseek(f->fp, f->pos, SEEK_SET);
#endif
}
