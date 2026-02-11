zoom_x (struct pixmap *source, struct pixmap *dest)
{
  int result = 0, dest_col, row, component, src_index;
  float ratio, src_ptr, delta;
  unsigned char src_component;

  if (source && dest)
    {


      if (source->height == dest->height
	  && source->components == dest->components)
	{
	  if (source->width < dest->width)
	    {
	      ratio = ((float) source->width / (float) dest->width);

	      for (src_ptr = 0, dest_col = 0; dest_col < dest->width;
		   src_ptr += ratio, dest_col++)
		{


		  src_index = (int) src_ptr;
		  delta = src_ptr - src_index;

		  for (row = 0; row < source->height; row++)
		    {
		      for (component = 0; component < source->components;
			   component++)
			{
			  src_component =
			    GET_COMP (source, src_index, row, component);

			  GET_COMP (dest, dest_col, row, component) =
			    src_component +
			    (GET_COMP (source, src_index + 1, row,
				       component) - src_component) * delta;
			}
		    }
		}
	    }
	  else
	    {
	      DBG (10, "zoom_x: error: can only zoom out\n");
	      result = -1;
	    }
	}
      else
	{
	  DBG (10, "zoom_x: error: incompatible pixmaps\n");
	  result = -1;
	}
    }

  return result;
}
