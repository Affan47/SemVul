road_by_activity(enum unit_activity act)
{
  road_type_iterate(road) {
    if (road->act == act) {
      return road;
    }
  } road_type_iterate_end;

  return NULL;
}
