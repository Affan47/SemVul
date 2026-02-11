ChangeCurrentTube(int count) {

  Ant  TheAnt;

  TheAnt = TheAnts.ants[TheAnts.curr_ant];

  while(count > 0) {
    if(TheAnt.current_tube == NULL)
      TheAnt.current_tube = TheAnt.first_tube;
    else {
      TheAnt.current_tube = TheAnt.current_tube->next;
      if(TheAnt.current_tube == NULL)
        TheAnt.current_tube = TheAnt.first_tube;
    }
    count--;
  }

  TheAnts.ants[TheAnts.curr_ant] = TheAnt;

}
