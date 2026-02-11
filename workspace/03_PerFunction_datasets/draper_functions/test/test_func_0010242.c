scan_rogue(graph *g, mesh *m, int aoff,int boff, int step, int end,
		       float *metric, edge *best, int *cross){
  int a,b;

  for(a=0;a+1<end;a++){
    for(b=a+1;b<end;b++){
      vertex *va = m->v[a*step+aoff];
      vertex *vb = m->v[b*step+boff];

      if(!va->selected && !vb->selected){
	if(!exists_edge(va,vb)){
	  int count = count_intersections(g,va,vb);
	  if(count){
	    float test = (b-a)/count;
	    if(test>=*metric){
	      *metric=test;
	      best->A=va;
	      best->B=vb;
	      *cross=count;
	    }
	  }
	}
      }
    }
  }
}
