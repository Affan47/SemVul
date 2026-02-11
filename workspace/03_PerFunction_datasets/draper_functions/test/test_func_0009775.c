png_colorspace_set_sRGB(png_const_structrp png_ptr, png_colorspacerp colorspace,
   int intent)
{


   static const png_XYZ sRGB_XYZ =
   {

       41239, 21264,  1933,
       35758, 71517, 11919,
       18048,  7219, 95053
   };


   if (colorspace->flags & PNG_COLORSPACE_INVALID)
      return 0;


   if (intent < 0 || intent >= PNG_sRGB_INTENT_LAST)
      return png_icc_profile_error(png_ptr, colorspace, "sRGB",
         (unsigned)intent, "invalid sRGB rendering intent");

   if ((colorspace->flags & PNG_COLORSPACE_HAVE_INTENT) != 0 &&
      colorspace->rendering_intent != intent)
      return png_icc_profile_error(png_ptr, colorspace, "sRGB",
         (unsigned)intent, "inconsistent rendering intents");

   if ((colorspace->flags & PNG_COLORSPACE_FROM_sRGB) != 0)
   {
      png_benign_error(png_ptr, "duplicate sRGB information ignored");
      return 0;
   }


   if ((colorspace->flags & PNG_COLORSPACE_HAVE_ENDPOINTS) != 0 &&
      !png_colorspace_endpoints_match(&sRGB_xy, &colorspace->end_points_xy,
         100))
      png_chunk_report(png_ptr, "cHRM chunk does not match sRGB",
         PNG_CHUNK_ERROR);


   (void)png_colorspace_check_gamma(png_ptr, colorspace, PNG_GAMMA_sRGB_INVERSE,
      2);


   colorspace->rendering_intent = (png_uint_16)intent;
   colorspace->flags |= PNG_COLORSPACE_HAVE_INTENT;


   colorspace->end_points_xy = sRGB_xy;
   colorspace->end_points_XYZ = sRGB_XYZ;
   colorspace->flags |=
      (PNG_COLORSPACE_HAVE_ENDPOINTS|PNG_COLORSPACE_ENDPOINTS_MATCH_sRGB);


   colorspace->gamma = PNG_GAMMA_sRGB_INVERSE;
   colorspace->flags |= PNG_COLORSPACE_HAVE_GAMMA;


   colorspace->flags |=
      (PNG_COLORSPACE_MATCHES_sRGB|PNG_COLORSPACE_FROM_sRGB);

   return 1;
}
