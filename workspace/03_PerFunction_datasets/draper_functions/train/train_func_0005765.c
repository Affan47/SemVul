master_clock_schedule_stage_updates (ClutterMasterClock *master_clock)
{
  ClutterStageManager *stage_manager = clutter_stage_manager_get_default ();
  const GSList *stages, *l;

  stages = clutter_stage_manager_peek_stages (stage_manager);

  for (l = stages; l != NULL; l = l->next)
    _clutter_stage_schedule_update (l->data);
}
