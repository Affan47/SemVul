corner_vertex(int index, int width, int height,
			 double *x, double *y)
{
  switch (index) {
  case 1:
    *x = 0.0;
    *y = height + 1;
    break;
  case 2:
    *x = 0.0;
    *y = 0.0;
    break;
  case 3:
    *x = width + 1;
    *y = 0.0;
    break;
  case 4:
    *x = width + 1;
    *y = height + 1;
  default:
    break;
  }
  index = index + 1;
  if(index > 4) index = 1;
  return(index);
}
