clone_image (image_t *image)


{
   image_t *new = alloc_image (image->width, image->height, image->color,
			       image->format);
   color_e band;

   for (band = first_band (new->color); band <= last_band (new->color); band++)
      if (new->format == FORMAT_4_2_0 && band != Y)
      {
	 memcpy (new->pixels [band], image->pixels [band],
		 ((new->width * new->height) >> 2) * sizeof (word_t));
      }
      else
      {
	 memcpy (new->pixels [band], image->pixels [band],
		 new->width * new->height * sizeof (word_t));
      }

   return new;
}
