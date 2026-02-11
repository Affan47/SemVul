clearQ()
{
  int time;
  int i;


  time = 0;
  while ((Qhead != -1) && (Q[Qhead].pitch == -1)) {
    time = time + Q[Qhead].delay;
    i = Qhead;
    Qhead = Q[i].next;
    Q[i].next = freehead;
    freehead = i;
  };
  if (Qhead != -1) {
    timestep(time, 1);
  };

  while (Qhead != -1) {
    event_error("Sustained notes beyond end of track");
    timestep(Q[Qhead].delay+1, 1);
  };
timestep(25,0);
}
