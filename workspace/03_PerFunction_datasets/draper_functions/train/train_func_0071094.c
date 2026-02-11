resize(int new_width, int new_height)
{
   if (get_xmax()-get_xmin()!=new_width ||
       get_ymax()-get_ymin()!=new_height)
   {
     gma_resize(new_width, new_height);
     bounds_initialized=false;
   }
}
