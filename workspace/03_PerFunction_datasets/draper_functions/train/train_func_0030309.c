mcache_sync(
    MCACHE *mp )
{
    CONSTR(FUNC, "mcache_sync");
    BKT *bp = NULL;
    intn ret_value = RET_SUCCESS;

#ifdef MCACHE_DEBUG
    (VOID)fprintf(stderr,"MCACHE_sync: entering \n");
#endif

    if (mp == NULL)
        HGOTO_ERROR(DFE_ARGS, FAIL);


    for (bp = mp->lqh.cqh_first; bp != (VOID *)&mp->lqh; bp = bp->q.cqe_next)
      {
          if (bp->flags & MCACHE_DIRTY && mcache_write(mp, bp) == RET_ERROR)
              HE_REPORT_GOTO("unable to flush a dirty page", FAIL);
      }

  done:
    if(ret_value == RET_ERROR)
      {
          return ret_value;
      }


#ifdef MCACHE_DEBUG
    (VOID)fprintf(stderr,"mcache_sync: exiting \n");
#endif

    return ret_value;
}
