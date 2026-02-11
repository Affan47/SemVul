event_sluroff(t)

int t;
{
  if (t == 0) {
    slurtotie();
    addfeature(SLUR_OFF, 0, 0, 0);
    v->inslur = 0;
  };
}
