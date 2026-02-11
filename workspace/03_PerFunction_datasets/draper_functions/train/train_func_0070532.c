drawing_in_bounds(gpaint_drawing *drawing, int x, int y)
{
   return (0<=x && x<=drawing->width && 0<=y && y<=drawing->height);
}
