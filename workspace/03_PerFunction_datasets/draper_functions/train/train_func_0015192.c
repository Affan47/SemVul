populate_neighbors(int vnum, mesh *m,
			       neighbors_grid *ng){
  int width = m->width;
  int y = vnum/width;
  int x = vnum - (y*width);
  int i;

  for(i=0;i<8;i++)ng->vnum[i]=-1;


  ng->center = m->v[vnum];
  ng->m = m;

  if(y-1 >= 0){
    if(x-1 >= 0)        ng->vnum[0]= (y-1)*width+(x-1);
                        ng->vnum[1]= (y-1)*width+x;
    if(x+1 <  m->width) ng->vnum[2]= (y-1)*width+(x+1);
  }

  if(x-1   >= 0)        ng->vnum[3]= y*width+(x-1);
  if(x+1   <  m->width) ng->vnum[4]= y*width+(x+1);

  if(y+1   < m->height){
    if(x-1 >= 0)        ng->vnum[5]= (y+1)*width+(x-1);
                        ng->vnum[6]= (y+1)*width+x;
    if(x+1 <  m->width) ng->vnum[7]= (y+1)*width+(x+1);
  }

}
