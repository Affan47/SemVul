automap_find_cycles(loc_node *location, automap_path *curpath)
{
  unsigned i;
  location->touched = TRUE;
  for(i = 0; i < NUM_DIRS; i++) {
    loc_node *thisdest = automap_edge_follow(location, i);
    if(thisdest && thisdest->found) {
      automap_path newnode;
      newnode.dir = i;
      newnode.loc = location;
      LEadd(curpath, newnode);

      if(thisdest->touched) {
	int cyclelength = 0;
	automap_path *p;
	cycleequation *cycle = NULL;
	cycleequation newcycle;
	for(p = curpath; p; p=p->next) {
	  int dir = p->dir;
	  newcycle.var = &(p->loc->outgoing[dir]->guess_length);
	  newcycle.min = &(p->loc->outgoing[dir]->min_length);
	  newcycle.xcoefficient = dirways[dir].deltax;
	  newcycle.ycoefficient = dirways[dir].deltay;
	  LEadd(cycle, newcycle);

	  cyclelength++;
	  if(p->loc == thisdest) {
	    if(cyclelength <= 2)
	      LEdestroy(cycle);
	    else
	      automap_add_cycle(cycle);
	    break;
	  }
	}
	if(!p) {
	  LEdestroy(cycle);
	}
      } else {
	automap_find_cycles(thisdest, curpath);
      }
      LEremove(curpath);
    }
  }
}
