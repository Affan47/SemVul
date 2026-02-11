mesh_setup(graph *g, mesh *m, int order, int divis){
  int flag=0;
  int wiggle=0;
  int n;
  m->width=3;
  m->height=2;
  {
    while(--order){
      if(flag){
	flag=0;
	m->height+=1;
      }else{
	flag=1;
	m->width+=2;
      }
    }
  }
  n=m->width*m->height;


  if(divis>0 && n%divis){
    while(1){
      wiggle++;

      if(!((n+wiggle)%divis)) break;

      if(n-wiggle>6 && !((n-wiggle)%divis)){
	wiggle = -wiggle;
	break;
      }
    }


    {
      int h = (int)sqrt(n+wiggle),w;

      while( (n+wiggle)%h )h--;

      if(h==1){

	h=2;
	w=(n+wiggle);
      }else{

	w = (n+wiggle)/h;
      }

      m->width=w;
      m->height=h;
    }
  }

  new_board(g, m->width * m->height);
  m->embed_list=0;


  {
    int x,y;
    vertex *v = g->verticies;
    for(y=0;y<m->height;y++)
      for(x=0;x<m->width;x++){
	v->x=x*50;
	v->y=y*50;
	v=v->next;
      }
  }

  g->objective = 0;
  g->objective_lessthan = 0;

}
