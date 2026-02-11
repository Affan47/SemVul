gregoriotex_write_note (FILE * f, gregorio_note * note, gregorio_glyph *glyph, gregorio_element *element, char next_note_pitch)
{
  unsigned int glyph_number;
  char temp;

  int type = AT_ONE_NOTE;
  if (!note)
    {
      gregorio_message (_
			("called with NULL pointer"),
			"gregoriotex_write_note", ERROR, 0);
      return;
    }

  gregoriotex_determine_note_number_and_type (note, glyph, element, &type, &glyph_number);

  if (note->shape == S_PUNCTUM_INCLINATUM)
    {
      if (note->previous)
	{

	  temp = note->previous->pitch - note->pitch;

	  switch (temp)
	    {


	    case -2:
	    case 2:
	      fprintf (f, "\\greendofglyph{10}%%\n");
	      break;
	    case -3:
	    case 3:
	      fprintf (f, "\\greendofglyph{11}%%\n");
	      break;
	    case -4:
	    case 4:
	      fprintf (f, "\\greendofglyph{11}%%\n");
	      break;
	    default:
	      fprintf (f, "\\greendofglyph{3}%%\n");
	      break;
	    }
	}
    }
  if (note->shape == S_PUNCTUM_INCLINATUM_DEMINUTUS)
    {
      if (note->previous)
	{

	  temp = note->previous->pitch - note->pitch;
	  if (temp < -2 || temp > 2)
	    {
	      fprintf (f, "\\greendofglyph{11}%%\n");
	    }
	  else
	    {
	      if (note->previous
		  && note->previous->shape == S_PUNCTUM_INCLINATUM_DEMINUTUS)
		{
		  if (temp < -1 || temp > 1)

		    {
		      fprintf (f, "\\greendofglyph{10}%%\n");
		    }
		  else
		    {
		      fprintf (f, "\\greendofglyph{8}%%\n");
		    }
		}
	      else
		{

		  fprintf (f, "\\greendofglyph{7}%%\n");
		}
	    }
	}
    }
  if (note->shape == S_PUNCTUM_INCLINATUM_AUCTUS)
    {
      if (note->previous)
	{

	  temp = note->previous->pitch - note->pitch;
	  if (temp < -1 || temp > 1)
	    {
	      fprintf (f, "\\greendofglyph{1}%%\n");
	    }
	  else
	    {

	      fprintf (f, "\\greendofglyph{3}%%\n");
	    }
	}
    }
  switch (note->shape)
    {
    case S_PUNCTUM_CAVUM:
      fprintf (f, "\\grepunctumcavum{%c}{%c}{%d}", note->pitch,
	       next_note_pitch, type);
      break;
    case S_LINEA_PUNCTUM_CAVUM:
      fprintf (f, "\\grelineapunctumcavum{%c}{%c}{%d}", note->pitch,
	       next_note_pitch, type);
      break;
    case S_LINEA:
      fprintf (f, "\\grelinea{%c}{%c}{%d}", note->pitch,
	       next_note_pitch, type);
      break;
    default:
      fprintf (f, "\\greglyph{\\char %d}{%c}{%c}{%d}",
	       glyph_number, note->pitch, next_note_pitch, type);
      break;
    }
}
