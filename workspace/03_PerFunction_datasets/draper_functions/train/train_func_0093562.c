same_points(const waypoint *A, const waypoint *B)
{
  return (
           (strcmp(A->shortname, B->shortname) == 0) &&
           (A->latitude == B->latitude) &&
           (A->longitude == B->longitude));
}
