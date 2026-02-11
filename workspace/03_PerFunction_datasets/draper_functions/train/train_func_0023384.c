Load_Subread(HITS_DB *db, int i, int beg, int end, char *read, int ascii)
{ FILE      *bases  = (FILE *) db->bases;
  int64      off;
  int        len, clen;
  int        bbeg, bend;
  HITS_READ *r = db->reads;

  if (bases == NULL)
    { db->bases = (void *) (bases = Fopen(Catenate(db->path,"","",".bps"),"r"));
      if (bases == NULL)
        exit (1);
    }
  if (i >= db->nreads)
    { fprintf(stderr,"%s: Index out of bounds (Load_Read)\n",Prog_Name);
      exit (1);
    }

  bbeg = beg/4;
  bend = (end-1)/4+1;

  off = r[i].boff + bbeg;
  len = end - beg;

  if (ftello(bases) != off)
    fseeko(bases,off,SEEK_SET);
  clen = bend-bbeg;
  if (clen > 0)
    { if (fread(read,clen,1,bases) != 1)
        SYSTEM_ERROR
    }
  Uncompress_Read(4*clen,read);
  read += beg%4;
  read[len] = 4;
  if (ascii == 1)
    { Lower_Read(read);
      read[-1] = '\0';
    }
  else if (ascii == 2)
    { Upper_Read(read);
      read[-1] = '\0';
    }
  else
    read[-1] = 4;

  return (read);
}
