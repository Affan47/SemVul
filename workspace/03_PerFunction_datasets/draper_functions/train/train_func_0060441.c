clear_eols(State *state)
{
  int i;
  if (pending_eols > 0) {
    for (i=0; i<pending_eols; i++) {
      printf("\n");
    }
    *state = B_OPEN;
    pending_eols = 0;
  }
}
