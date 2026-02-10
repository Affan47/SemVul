decode_range (unsigned range_state, unsigned range_label, unsigned range_level,
	      word_t **domain, wfa_t *wfa)


{
   unsigned   root_state [3];
   image_t   *state_image;
   word_t   **images;

   u_word_t  *offsets;

   word_t    *range;

   enlarge_image (range_level - (wfa->level_of_state [range_state] - 1),
		  FORMAT_4_4_4, -1, wfa);
   root_state [0] = range_state;
   state_image    = alloc_image (width_of_level (range_level + 1),
				 height_of_level (range_level + 1),
				 NO, FORMAT_4_4_4);
   alloc_state_images (&images, &offsets, state_image, NULL, range_state,
		       range_level + 1, NO, wfa);
   compute_state_images (range_level + 1, images, offsets, wfa);

   range = fiasco_calloc (size_of_level (range_level), sizeof (word_t));

   if ((range_level & 1) == 0)
   {
      memcpy (range,
	      images [range_state + (range_level + 1) * wfa->states]
	      + range_label * size_of_level (range_level),
	      size_of_level (range_level) * sizeof (word_t));
   }
   else
   {
      word_t   *src, *dst;
      unsigned  y;

      src = images [range_state + (range_level + 1) * wfa->states]
	    + range_label * width_of_level (range_level);
      dst = range;
      for (y = height_of_level (range_level); y; y--)
      {
	 memcpy (dst, src, width_of_level (range_level) * sizeof (word_t));
	 dst += width_of_level (range_level);
	 src += width_of_level (range_level + 1);
      }
   }

   if (domain != NULL)
   {
      int      s;
      unsigned edge;

      if (ischild (s = wfa->tree [range_state][range_label]))
	 *domain++ = duplicate_state_image (images [s + (range_level)
						   * wfa->states],
					    offsets [s + (range_level)
						    * wfa->states],
					    range_level);
      for (edge = 0; isedge (s = wfa->into[range_state][range_label][edge]);
	   edge++)
	 *domain++ = duplicate_state_image (images [s + (range_level)
						   * wfa->states],
					    offsets [s + (range_level)
						    * wfa->states],
					    range_level);
      *domain = NULL;
   }

   free_state_images (range_level + 1, NO, images, offsets, NULL, range_state,
		      NO, wfa);
   free_image (state_image);

   return range;
}
