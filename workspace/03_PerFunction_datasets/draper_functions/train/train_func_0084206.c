ScaleCurrentWall(double sx, double sy, double sz) {

  Tube *current;

  current = TheAnts.ants[TheAnts.curr_ant].current_tube;
  if (current->type == IS_WALL) {
    TheAnts.ants[TheAnts.curr_ant].current_tube->e2.x += sx;
    TheAnts.ants[TheAnts.curr_ant].current_tube->e2.y += sy;
    TheAnts.ants[TheAnts.curr_ant].current_tube->e2.z += sz;
  }

}
