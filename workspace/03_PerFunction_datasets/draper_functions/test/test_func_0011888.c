gregorio_determine_next_pitch
  (gregorio_syllable * syllable, gregorio_element * element,
   gregorio_glyph * glyph)
{
  char temp;
  if (!element || !syllable)
    {
      gregorio_message (_
			("called with a NULL argument"),
			"gregorio_determine_next_pitch",
			ERROR, 0);
      return 'g';
    }

  if (glyph)
    {
      glyph = glyph->next;
      while (glyph)
        {
          if (glyph->type == GRE_GLYPH && glyph->first_note)
	    {
	      return glyph->first_note->pitch;
	    }
          glyph = glyph->next;
        }
    }

  element = element->next;
  while (element)
    {
      if (element->type == GRE_ELEMENT && element->first_glyph)
	{
	  glyph = element->first_glyph;
	  while (glyph)
	    {
	      if (glyph->type == GRE_GLYPH && glyph->first_note)
		{
		  return glyph->first_note->pitch;
		}
	      glyph = glyph->next;
	    }
	}
      element = element->next;
    }


  syllable = syllable->next_syllable;
  while (syllable)
    {

      temp = gregorio_syllable_first_note (syllable);
      if (temp)
	{
	  return temp;
	}
      syllable = syllable->next_syllable;
    }

  return 'g';
}
