DrawState (FILE *out, state_t *state, toptions_t *options, int color)


{

   if (isrange (state->multistate))
   {
      if (state->mc [0] == NONE && state->mc [1] == NONE)
	 DrawSingleState (out, state->x, state->y, state->state_nr,
			  options, color);
      else
	 DrawMCState(out, state->x, state->y, state->state_nr, options,
		     state->mc[0], state->mc[1], color);
   }
   else
      DrawMultistate(out,state->x, state->y, state->multistate, state->state_nr,
		     options, color);
}
