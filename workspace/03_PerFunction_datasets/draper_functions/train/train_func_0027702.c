gregorio_mix_h_episemus (gregorio_note * current_note, unsigned char type)
{
  gregorio_note *prev_note = NULL;
  if (!current_note)
    {
      gregorio_message (_("function called with NULL argument"),
			   "gregorio_mix_h_episemus", WARNING, 0);
      return;
    }

  if (current_note->type != GRE_NOTE)
    {
      current_note->h_episemus_type = H_ALONE;
    }
  prev_note = current_note->previous;
  if (type == H_NO_EPISEMUS)
    {
      gregorio_set_h_episemus(current_note, H_NO_EPISEMUS);
      current_note->h_episemus_top_note = 0;
    }
  else
    {
      if (prev_note && prev_note->type == GRE_NOTE)
        {
          current_note->h_episemus_top_note = max(prev_note->pitch, current_note->pitch);
        }
      else
        {
          current_note->h_episemus_top_note = current_note->pitch;
        }
      if (!prev_note || prev_note->type != GRE_NOTE
	  || simple_htype(prev_note->h_episemus_type) == H_NO_EPISEMUS)
	{
	  gregorio_set_h_episemus(current_note, H_ALONE);
	}
      else
	{
	  gregorio_set_h_episemus(current_note, H_MULTI);
	  if (simple_htype(prev_note->h_episemus_type) != H_MULTI)
	    {
	      gregorio_set_h_episemus(prev_note, H_MULTI);
	    }
	  gregorio_determine_good_top_notes (current_note);
	}
    }
}
