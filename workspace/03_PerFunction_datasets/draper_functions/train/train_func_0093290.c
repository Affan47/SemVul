ShrinkButton(button_info *b, container_info *c)
{
  int i,j,k,l;

  if (!b)
  {
    fprintf(stderr,"error: shrink1: button is empty but shouldn't\n");
    exit(1);
  }
  i = b->BPosX+b->BPosY*c->num_columns;

  for(k=0;k<b->BHeight;k++)
  {
    for(j=0;j<b->BWidth;j++)
    {
      if(j||k)
      {
	l = i+j+k*c->num_columns;
	if (c->buttons[l] != b)
	{
	  fprintf(stderr,"error: shrink2: button was stolen\n");
	  exit(1);
	}
	c->buttons[l] = NULL;
      }
    }
  }
}
