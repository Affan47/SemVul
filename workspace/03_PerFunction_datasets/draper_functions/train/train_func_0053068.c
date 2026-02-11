i945_miptree_layout_3d(struct intel_mipmap_tree * mt)
{
   GLuint width = mt->physical_width0;
   GLuint height = mt->physical_height0;
   GLuint depth = mt->physical_depth0;
   GLuint pack_x_pitch, pack_x_nr;
   GLuint pack_y_pitch;
   GLuint level;

   mt->total_width = mt->physical_width0;
   mt->total_height = 0;

   pack_y_pitch = MAX2(mt->physical_height0, 2);
   pack_x_pitch = mt->total_width;
   pack_x_nr = 1;

   for (level = mt->first_level; level <= mt->last_level; level++) {
      GLint x = 0;
      GLint y = 0;
      GLint q, j;

      intel_miptree_set_level_info(mt, level,
				   0, mt->total_height,
				   width, height, depth);

      for (q = 0; q < depth;) {
	 for (j = 0; j < pack_x_nr && q < depth; j++, q++) {
	    intel_miptree_set_image_offset(mt, level, q, x, y);
	    x += pack_x_pitch;
	 }

	 x = 0;
	 y += pack_y_pitch;
      }

      mt->total_height += y;

      if (pack_x_pitch > 4) {
	 pack_x_pitch >>= 1;
	 pack_x_nr <<= 1;
	 assert(pack_x_pitch * pack_x_nr <= mt->total_width);
      }

      if (pack_y_pitch > 2) {
	 pack_y_pitch >>= 1;
      }

      width = minify(width, 1);
      height = minify(height, 1);
      depth = minify(depth, 1);
   }
}
