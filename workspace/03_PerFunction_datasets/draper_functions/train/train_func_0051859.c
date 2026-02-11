DrawMultistate (FILE *out, int x, int y, int state1, int state2,
		toptions_t *options, int color)


{
   if (options->with_shadows)
      xfig_triangle (out, x + SHADOW_OFFSET,y + SHADOW_OFFSET,
		     MULTISTATE_HEIGHT, MULTISTATE_WIDTH, SHADOW_COLOR,
		     SHADOW_COLOR, STATE_LEVEL + 1);
   if (color != DEFAULT)
      xfig_triangle (out, x, y, MULTISTATE_HEIGHT, MULTISTATE_WIDTH,
		     MULTISTATE_COLOR, color, STATE_LEVEL);
   else
      xfig_triangle (out, x, y, MULTISTATE_HEIGHT, MULTISTATE_WIDTH,
		     MULTISTATE_COLOR, MULTISTATE_FILL_COLOR, STATE_LEVEL);

   if (options->state_text)
      fprintf(out, "4 1 %d %d 0 0 %d 0.0000 4 50 120 %d %d %d     %d\\001\n",
	      TEXT_COLOR, TEXT_LEVEL, STATE_RADIUS / 20,
	      x + 5, y + 25, state1, state2);
}
