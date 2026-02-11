f_read(File *f, unsigned char *dest, long bytes)
{
#ifdef FBUF
   long done = 0, off = 0;
   int c;
   unsigned char *p;
   _f_read_pos(f, f->pos, bytes);

   c = f->pos / CHUNK_SIZE;
   off = f->pos - (c * CHUNK_SIZE);
   p = dest;
   while ((done < bytes) && (c < f->chunk_num))
     {
        long amount = bytes - done;

        if (!f->chunk[c]) break;
        if (amount > (f->chunk[c]->size - off))
           amount = (f->chunk[c]->size - off);
        if (amount < 1) return 0;
        memcpy(p, f->chunk[c]->data + off, amount);
        p += amount;
        off = 0;
        done += amount;
        c++;
     }
   f->pos += done;
   return done;
#else
   long done = gzread(f->fp, dest, bytes);
   f->pos += done;
   return done;
#endif
}
