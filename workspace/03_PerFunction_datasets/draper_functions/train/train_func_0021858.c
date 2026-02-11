button_set_state(Gameboard *g, buttonstate *b, int rollover, int press){
  int i;
  buttonstate *states=g->b.states;

  if(b->rollover == rollover && b->press == press)return;

  for(i=0;i<NUMBUTTONS;i++){
    buttonstate *bb=states+i;
    if(bb->position>0){
      if(bb!=b){
	if(bb->rollover)
	  invalidate_rollover(g,bb);
	if(bb->press)
	  invalidate_button(g,bb);

	bb->rollover=0;
	bb->press=0;
      }else{
	if(bb->rollover != rollover)
	  invalidate_rollover(g,bb);
	if(bb->press != press)
	  invalidate_button(g,bb);

	bb->rollover=rollover;
	bb->press=press;
      }
    }
  }
  g->b.allclear=0;
}
