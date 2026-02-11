smem_create(char *filename, int *driverhandle)
 { DAL_SHM_SEGHEAD *sp;
   int h, sz, nitems;

   if (NULL == filename) return(SHARED_NULPTR);
   if (NULL == driverhandle) return(SHARED_NULPTR);
   nitems = sscanf(filename, "h%d", &h);
   if (1 != nitems) return(SHARED_BADARG);

   if (SHARED_INVALID == (h = shared_malloc(sz = 2880 + sizeof(DAL_SHM_SEGHEAD),
                        SHARED_RESIZE | SHARED_PERSIST, h)))
     return(SHARED_NOMEM);

   if (NULL == (sp = (DAL_SHM_SEGHEAD *)shared_lock(h, SHARED_RDWRITE)))
     { shared_free(h);
       return(SHARED_BADARG);
     }

   sp->ID = DAL_SHM_SEGHEAD_ID;
   sp->h = h;
   sp->size = sz;
   sp->nodeidx = -1;

   *driverhandle = h;

   return(0);
 }
