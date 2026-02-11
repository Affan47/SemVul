is_in_bounds(glui32 x1, glui32 y1, glui32 width1, glui32 height1,
		 glui32 x2, glui32 y2, glui32 width2, glui32 height2)
{
  return (x1 >= x2 && y1 >= y2 &&
	  x1 + width1 <= x2 + width2 && y1 + height1 <= y2 + height2);
}
