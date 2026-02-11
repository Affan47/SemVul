png_get_cHRM_XYZ_fixed(png_structp png_ptr, png_const_infop info_ptr,
    png_fixed_point *int_red_X, png_fixed_point *int_red_Y,
    png_fixed_point *int_red_Z, png_fixed_point *int_green_X,
    png_fixed_point *int_green_Y, png_fixed_point *int_green_Z,
    png_fixed_point *int_blue_X, png_fixed_point *int_blue_Y,
    png_fixed_point *int_blue_Z)
{
   if (png_ptr != NULL && info_ptr != NULL && (info_ptr->valid & PNG_INFO_cHRM))
   {
      png_xy xy;
      png_XYZ XYZ;

      png_debug1(1, "in %s retrieval function", "cHRM_XYZ");

      xy.whitex = info_ptr->x_white;
      xy.whitey = info_ptr->y_white;
      xy.redx = info_ptr->x_red;
      xy.redy = info_ptr->y_red;
      xy.greenx = info_ptr->x_green;
      xy.greeny = info_ptr->y_green;
      xy.bluex = info_ptr->x_blue;
      xy.bluey = info_ptr->y_blue;


      if (png_XYZ_from_xy_checked(png_ptr, &XYZ, xy))
      {
         if (int_red_X != NULL)
            *int_red_X = XYZ.redX;
         if (int_red_Y != NULL)
            *int_red_Y = XYZ.redY;
         if (int_red_Z != NULL)
            *int_red_Z = XYZ.redZ;
         if (int_green_X != NULL)
            *int_green_X = XYZ.greenX;
         if (int_green_Y != NULL)
            *int_green_Y = XYZ.greenY;
         if (int_green_Z != NULL)
            *int_green_Z = XYZ.greenZ;
         if (int_blue_X != NULL)
            *int_blue_X = XYZ.blueX;
         if (int_blue_Y != NULL)
            *int_blue_Y = XYZ.blueY;
         if (int_blue_Z != NULL)
            *int_blue_Z = XYZ.blueZ;

         return (PNG_INFO_cHRM);
      }
   }

   return (0);
}
