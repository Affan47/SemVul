gregorio_add_h_episemus (gregorio_note *note, unsigned char type, unsigned int *nbof_isolated_episemus)
{
  if (!note || (note->type != GRE_NOTE && note->type != GRE_BAR))
    {
      gregorio_message (_("trying to add an horizontal episemus on something that is not a note"),
			   "add_h_episemus", ERROR, 0);
      return;
    }
  if (!nbof_isolated_episemus)
    {
      gregorio_message (_("NULL argument nbof_isolated_episemus"),
			   "add_h_episemus", FATAL_ERROR, 0);
      return;
    }
  if (type == H_BOTTOM)
    {
      note->h_episemus_type = note->h_episemus_type | H_BOTTOM;
      return;
    }
  if (!note->h_episemus_top_note || *nbof_isolated_episemus == 0)
    {
      gregorio_mix_h_episemus (note, H_ONE);
      *nbof_isolated_episemus = 1;
    }
  else
    {
      gregorio_activate_isolated_h_episemus (note, *nbof_isolated_episemus);
      *nbof_isolated_episemus = *nbof_isolated_episemus +1;
    }
}
