region_intersects(edge *e){

  region_segment *s=r.l;
  while(s){
    if(s->layout<3){
      if(s->radius!=0){
	if(intersects_arc(e,s))return 1;
      }else{
	double xdummy,ydummy;

	if(intersects(e->A->x,e->A->y,e->B->x,e->B->y,
		      s->x1,s->y1,s->x2,s->y2,
		      &xdummy,&ydummy))return 1;

      }
    }
    s=s->next;
  }
  return 0;
}
