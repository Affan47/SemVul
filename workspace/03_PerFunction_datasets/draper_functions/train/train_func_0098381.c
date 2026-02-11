VTThrd_delete(VTThrd* thrd, uint32_t tid)
{
  if ( !thrd ) return;

#if !defined(VT_DISABLE_RFG)
  if ( thrd->rfg_regions )
    RFG_Regions_free(thrd->rfg_regions);
#endif


#if defined(VT_PLUGIN_CNTR)

  if ( vt_plugin_cntr_used && thrd->plugin_cntr_defines && !(thrd->is_virtual) )
    vt_plugin_cntr_thread_exit(thrd);
#endif

  if ( thrd->gen )
    VTGen_delete(thrd->gen);

#if defined(VT_RUSAGE)
  if ( vt_rusage_num() > 0 && !(thrd->is_virtual) )
  {
    if ( thrd->ru_obj )
    {
      vt_rusage_free(thrd->ru_obj);
      thrd->ru_obj = NULL;
    }
    if ( thrd->ru_valv )
    {
      free(thrd->ru_valv);
      thrd->ru_valv = NULL;
    }
  }
#endif

#if defined(VT_METR)
  if ( vt_metric_num() > 0 && !(thrd->is_virtual) )
  {
    if ( thrd->metv )
    {
      vt_metric_free(thrd->metv, tid);
      thrd->metv = NULL;
    }
    if ( thrd->offv )
    {
      free( thrd->offv );
      thrd->offv = NULL;
    }
    if ( thrd->valv )
    {
      free(thrd->valv);
      thrd->valv = NULL;
    }
  }
#endif
  free(thrd);


#if (defined(VT_MT) || defined(VT_HYB) || defined(VT_JAVA))
  VTTHRD_LOCK_ENV();
  VTThrdn--;
  vt_cntl_msg(2, "Thread object #%u deleted, leaving %u", tid, VTThrdn);
  VTTHRD_UNLOCK_ENV();
#else
  VTThrdn--;
  vt_cntl_msg(2, "Thread object #%u deleted, leaving %u", tid, VTThrdn);
#endif
}
