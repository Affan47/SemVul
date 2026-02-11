qmonCreateSchedConfig(
Widget parent
) {
   Widget sconf_layout, sconf_ok, sconf_cancel,
          sconf_main_link, sconf_lad_timePB,
          sconf_schedule_intervalPB, sconf_reprioritize_intervalPB,
          sconf_load_name, sconf_load_value, sconf_load_namePB,
          sconf_load_add, sconf_load_delete, sconf_default_durationPB;

   DENTER(TOP_LAYER, "qmonCreateSchedConfig");

   sconf_layout = XmtBuildQueryDialog( parent, "sconf_shell",
                           sc_resources, XtNumber(sc_resources),
                           "sconf_main_link", &sconf_main_link,
                           "sconf_ok", &sconf_ok,
                           "sconf_cancel", &sconf_cancel,
                           "sconf_algorithm", &sconf_algorithm,
                           "sconf_schedule_interval", &sconf_schedule_interval,
                           "sconf_sc_params", &sconf_sc_params,
                           "sconf_maxujobs", &sconf_maxujobs,
                           "sconf_flush_submit_secs", &sconf_flush_submit_secs,
                           "sconf_flush_finish_secs", &sconf_flush_finish_secs,
                           "sconf_max_reservation", &sconf_max_reservation,
                           "sconf_lad_time", &sconf_lad_time,
                           "sconf_load_formula", &sconf_load_formula,
                           "sconf_load_adjustments", &sconf_load_adjustments,
                           "sconf_load_name", &sconf_load_name,
                           "sconf_load_namePB", &sconf_load_namePB,
                           "sconf_load_value", &sconf_load_value,
                           "sconf_load_add", &sconf_load_add,
                           "sconf_load_delete", &sconf_load_delete,
                           "sconf_reprioritize_interval",
                                 &sconf_reprioritize_interval,
                           "sconf_default_duration",
                                 &sconf_default_duration,
                           "sconf_queue_sort_method", &sconf_queue_sort_method,
                           "sconf_lad_timePB", &sconf_lad_timePB,
                           "sconf_schedule_intervalPB",
                                 &sconf_schedule_intervalPB,
                           "sconf_reprioritize_intervalPB",
                                 &sconf_reprioritize_intervalPB,
                           "sconf_default_durationPB",
                                 &sconf_default_durationPB,
                           "sconf_job_info", &sconf_job_info,
                           "sconf_job_range", &sconf_job_range,
                           NULL);

   XtAddCallback(sconf_main_link, XmNactivateCallback,
                     qmonMainControlRaise, NULL);
   XtAddCallback(sconf_cancel, XmNactivateCallback,
                     qmonSchedCancel, NULL);
   XtAddCallback(sconf_ok, XmNactivateCallback,
                     qmonSchedOk, NULL);


   XtAddCallback(sconf_lad_timePB, XmNactivateCallback,
                 qmonSchedTime, (XtPointer)sconf_lad_time);
   XtAddCallback(sconf_schedule_intervalPB, XmNactivateCallback,
                 qmonSchedTime, (XtPointer)sconf_schedule_interval);
   XtAddCallback(sconf_reprioritize_intervalPB, XmNactivateCallback,
                 qmonSchedTime, (XtPointer)sconf_reprioritize_interval);
   XtAddCallback(sconf_default_durationPB, XmNactivateCallback,
                 qmonSchedTime, (XtPointer)sconf_default_duration);


   XtAddCallback(sconf_load_adjustments, XmNlabelActivateCallback,
                  qmonLoadNamesSC, NULL);

   XtAddCallback(sconf_job_info, XmtNvalueChangedCallback,
                  qmonSchedJobInfo, NULL);

   XtAddEventHandler(XtParent(sconf_layout), StructureNotifyMask, False,
                        SetMinShellSize, NULL);
   XtAddEventHandler(XtParent(sconf_layout), StructureNotifyMask, False,
                        SetMaxShellSize, NULL);
   DEXIT;
   return sconf_layout;
}
