free_soid_list (SOID_T *root) {
  if (root != NO_SOID) {
    SOID_T *q;
    for (q = root; NEXT (q) != NO_SOID; FORWARD (q)) {
      ;
    }
    NEXT (q) = top_soid_list;
    top_soid_list = root;
  }
}
