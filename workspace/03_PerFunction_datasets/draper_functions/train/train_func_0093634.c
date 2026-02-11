callback_function(void * ID, vt_plugin_cntr_timevalue tv) {
  vt_plugin_cntr_timevalue * timeList;
  struct vt_plugin_single_counter * defines =
      (struct vt_plugin_single_counter *) ID;
  if (defines == NULL)
    return -1;

  if (defines->callback_values == NULL)
    return -1;

  if (defines->current_callback_write_position >= max_values_callback)
    return VT_PLUGIN_CNTR_CALLBACK_BUFFER_FULL;

#if (defined(VT_MT) || defined (VT_HYB) || defined(VT_JAVA))
  VTThrd_lock((VTThrdMutex **) &defines->callback_mutex);
#endif

  timeList = defines->callback_values;
  if (timeList == NULL) {
#if (defined(VT_MT) || defined (VT_HYB) || defined(VT_JAVA))
    VTThrd_unlock((VTThrdMutex **) &defines->callback_mutex);
#endif
    return -1;
  }

  if (defines->current_callback_write_position >= max_values_callback) {
#if (defined(VT_MT) || defined (VT_HYB) || defined(VT_JAVA))
    VTThrd_unlock((VTThrdMutex **) &defines->callback_mutex);
#endif
    return VT_PLUGIN_CNTR_CALLBACK_BUFFER_FULL;
  }

  if (VTTHRD_TRACE_STATUS(VTThrdv[defines->tid]) == VT_TRACE_OFF_PERMANENT) {
#if (defined(VT_MT) || defined (VT_HYB) || defined(VT_JAVA))
    VTThrd_unlock((VTThrdMutex **) &defines->callback_mutex);
#endif
    return VT_PLUGIN_CNTR_CALLBACK_TRACE_OFF_PERMANENT;
  }

  timeList[defines->current_callback_write_position++] = tv;

#if (defined(VT_MT) || defined (VT_HYB) || defined(VT_JAVA))
  VTThrd_unlock((VTThrdMutex **) &defines->callback_mutex);
#endif

  return VT_PLUGIN_CNTR_CALLBACK_OK;
}
