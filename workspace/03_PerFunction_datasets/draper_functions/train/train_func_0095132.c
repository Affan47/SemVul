png_colorspace_set_gamma(png_const_structrp png_ptr,
   png_colorspacerp colorspace, png_fixed_point gAMA)
{


   png_const_charp errmsg;

   if (gAMA < 16 || gAMA > 625000000)
      errmsg = "gamma value out of range";

#  ifdef PNG_READ_gAMA_SUPPORTED

      else if ((png_ptr->mode & PNG_IS_READ_STRUCT) != 0 &&
         (colorspace->flags & PNG_COLORSPACE_FROM_gAMA) != 0)
         errmsg = "duplicate";
#  endif


   else if (colorspace->flags & PNG_COLORSPACE_INVALID)
      return;

   else
   {
      if (png_colorspace_check_gamma(png_ptr, colorspace, gAMA, 1))
      {

         colorspace->gamma = gAMA;
         colorspace->flags |=
            (PNG_COLORSPACE_HAVE_GAMMA | PNG_COLORSPACE_FROM_gAMA);
      }


      return;
   }


   colorspace->flags |= PNG_COLORSPACE_INVALID;
   png_chunk_report(png_ptr, errmsg, PNG_CHUNK_WRITE_ERROR);
}
