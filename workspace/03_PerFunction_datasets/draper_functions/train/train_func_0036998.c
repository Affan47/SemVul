compute_total_up (List_T gregions) {
  long int total_up;
  List_T p;
  Gregion_T gregion;

  total_up = 0;
  for (p = gregions; p != NULL; p = List_next(p)) {
    gregion = (Gregion_T) List_head(p);
    total_up += 1;
    gregion->total_up = total_up;
  }

  return;
}
