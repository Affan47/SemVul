i945_miptree_layout_cube(struct intel_mipmap_tree * mt)
{
   const GLuint dim = mt->physical_width0;
   GLuint face;
   GLuint lvlWidth = mt->physical_width0, lvlHeight = mt->physical_height0;
   GLint level;

   assert(lvlWidth == lvlHeight);


   if (dim > 32)
      mt->total_width = dim * 2;
   else
      mt->total_width = 14 * 8;

   if (dim >= 4)
      mt->total_height = dim * 4 + 4;
   else
      mt->total_height = 4;


   for (level = mt->first_level; level <= mt->last_level; level++) {
      intel_miptree_set_level_info(mt, level,
				   0, 0,
				   lvlWidth, lvlHeight, 6);
      lvlWidth /= 2;
      lvlHeight /= 2;
   }

   for (face = 0; face < 6; face++) {
      GLuint x = initial_offsets[face][0] * dim;
      GLuint y = initial_offsets[face][1] * dim;
      GLuint d = dim;

      if (dim == 4 && face >= 4) {
	 y = mt->total_height - 4;
	 x = (face - 4) * 8;
      } else if (dim < 4 && (face > 0 || mt->first_level > 0)) {
	 y = mt->total_height - 4;
	 x = face * 8;
      }

      for (level = mt->first_level; level <= mt->last_level; level++) {
	 intel_miptree_set_image_offset(mt, level, face, x, y);

	 d >>= 1;

	 switch (d) {
	 case 4:
	    switch (face) {
	    case FACE_POS_X:
	    case FACE_NEG_X:
	       x += step_offsets[face][0] * d;
	       y += step_offsets[face][1] * d;
	       break;
	    case FACE_POS_Y:
	    case FACE_NEG_Y:
	       y += 12;
	       x -= 8;
	       break;
	    case FACE_POS_Z:
	    case FACE_NEG_Z:
	       y = mt->total_height - 4;
	       x = (face - 4) * 8;
	       break;
	    }
	    break;

	 case 2:
	    y = mt->total_height - 4;
	    x = bottom_offsets[face];
	    break;

	 case 1:
	    x += 48;
	    break;

	 default:
	    x += step_offsets[face][0] * d;
	    y += step_offsets[face][1] * d;
	    break;
	 }
      }
   }
}
