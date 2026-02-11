m_fix_grads()
{ int me = GET_THREAD_ID;
  int pnum;
  int i,k;
  struct procforce *p;
  REAL *f;

  for ( pnum = 0 ; pnum < nprocs ; pnum++ )
  { for ( k = phead[me][pnum] ; k >= 0 ; k = p->next )
     { p = pbase[pnum] + k;
        f = get_force(p->v_id);
        for ( i = 0 ; i < SDIM ; i++ ) f[i] += p->f[i];
     }
  }
}
