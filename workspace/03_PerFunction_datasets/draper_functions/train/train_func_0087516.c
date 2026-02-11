turn_on_field(struct state *st, int ff)
{
  if (!st->fon[ff]) {

    st->acc[ff]=0.02 * myrnd();
    st->vel[ff]=0.0;
    st->var[ff]=st->op[ff];
  }
  st->fon[ff] = 1;
  if (ff == 10) {
    turn_on_field(st, 11);
    turn_on_field(st, 12);
  }
  if (ff == 13) {
    turn_on_field(st, 14);
    turn_on_field(st, 15);
  }
}
