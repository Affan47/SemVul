PlaceAndExpandButton(int x, int y, button_info *b, button_info *ub)
{
  int i,j,k;
  container_info *c=ub->c;

  i = x+y*c->num_columns;
  if (x>=c->num_columns || x<0)
  {
    fprintf(stderr,"%s: Button out of horizontal range. Quitting.\n",MyName);
    fprintf(stderr,"Button=%d num_columns=%d BPosX=%d\n",
	    i,c->num_columns,b->BPosX);
    exit(1);
  }
  if (y>=c->num_rows || y<0)
  {
    if (b->flags.b_PosFixed || !ub->c->flags.b_SizeSmart || y<0)
    {
      fprintf(stderr,"%s: Button out of vertical range. Quitting.\n",
	      MyName);
      fprintf(stderr,"Button=%d num_rows=%d BPosY=%d\n",
	      i,c->num_rows,b->BPosY);
      exit(1);
    }
    c->num_rows=y+b->BHeight;
    c->num_buttons=c->num_columns*c->num_rows;
    alloc_buttonlist(ub,c->num_buttons);
  }
  if(x+b->BWidth>c->num_columns)
  {
    fprintf(stderr,"%s: Button too wide. giving up\n",MyName);
    fprintf(stderr,"Button=%d num_columns=%d bwidth=%d w=%d\n",
	    i,c->num_columns,b->BWidth,x);
    b->BWidth = c->num_columns-x;
  }
  if(y+b->BHeight>c->num_rows)
  {
    if (c->flags.b_SizeSmart)
    {
      c->num_rows=y+b->BHeight;
      c->num_buttons=c->num_columns*c->num_rows;
      alloc_buttonlist(ub,c->num_buttons);
    }
    else
    {
      fprintf(stderr,"%s: Button too tall. Giving up\n",MyName);
      fprintf(stderr,"Button=%d num_rows=%d bheight=%d h=%d\n",
	      i,c->num_rows,b->BHeight,y);
      b->BHeight = c->num_rows-y;
    }
  }


  for(k=0;k<b->BHeight;k++)
    for(j=0;j<b->BWidth;j++)
      if (c->buttons[i+j+k*c->num_columns])
	return 1;

  for(k=0;k<b->BHeight;k++)
    for(j=0;j<b->BWidth;j++)
      c->buttons[i+j+k*c->num_columns] = b;
  b->BPosX = x;
  b->BPosY = y;
  return 0;
}
