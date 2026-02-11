MoveCurrentWall(double dx, double dy, double dz) {

  Tube *current;

  if(TheAnts.ants[TheAnts.curr_ant].current_tube != NULL) {
    current = TheAnts.ants[TheAnts.curr_ant].current_tube;
    if (current->type == IS_WALL) {
      TheAnts.ants[TheAnts.curr_ant].current_tube->e1.x += dx;
      TheAnts.ants[TheAnts.curr_ant].current_tube->e1.y += dy;
      TheAnts.ants[TheAnts.curr_ant].current_tube->e1.z += dz;
      TheAnts.ants[TheAnts.curr_ant].current_tube->e2.x += dx;
      TheAnts.ants[TheAnts.curr_ant].current_tube->e2.y += dy;
      TheAnts.ants[TheAnts.curr_ant].current_tube->e2.z += dz;
    }
  }

}
