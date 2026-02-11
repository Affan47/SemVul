reset_young_targets(Space* space, Space* target) {
  FOR_YOUNG_AREAS(space->small_area, area->target_space = target);


  FOR_YOUNG_AREAS(space->weaks_area, area->target_space = target);
}
