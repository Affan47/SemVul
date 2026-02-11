set_file_position(off_t newpos, bool seek) {
  fposition_rep = newpos;
  if (fposition_rep >= flength_rep) {
    fposition_rep = flength_rep;
    file_ready_rep = false;
    file_ended_rep = true;
  }
  else {
    file_ready_rep = true;
    file_ended_rep = false;
  }
}
