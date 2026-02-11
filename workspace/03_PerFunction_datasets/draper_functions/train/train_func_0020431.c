findItem(int rootX_,int rootY_)
{
  MSMenuItem *mi;
  int X, Y;
  rootXY (X,Y);
  int xcoord = rootX_-X;
  int ycoord = rootY_-Y;
  int i,n=itemVector().length();
  for(i=0;i<n;i++)
   {
     mi=(MSMenuItem*)itemVector()(i);
     if (xcoord>=mi->x()&&ycoord>=mi->y()&&
	 xcoord<=mi->x()+mi->width()&&ycoord<=mi->y()+mi->height())
      { return (mi->sensitive()==MSTrue)?mi:0; }
   }
  return 0;
}
