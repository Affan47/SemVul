WhichButton(ButtonArray *array,int x, int y)
{
int num;
  num=y/(array->h+1);
  if (x<array->x || x>array->x+array->w || num<0 || num>array->count-1) num=-1;
  return(num);
}
