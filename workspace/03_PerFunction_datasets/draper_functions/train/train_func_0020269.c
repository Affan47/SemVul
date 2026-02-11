VTThrd_close(VTThrd* thrd)
{
  if ( !thrd ) return;

#if defined(VT_PLUGIN_CNTR)
  if ( vt_plugin_cntr_used && thrd->plugin_cntr_defines ){

    vt_plugin_cntr_write_post_mortem(thrd);
  }
#endif
  VTGen_close(thrd->gen);
}
