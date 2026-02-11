gregorio_first_glyph (gregorio_syllable * syllable)
{
  gregorio_glyph *glyph;
  gregorio_element *element;
  if (!syllable)
    {
      gregorio_message (_
			("called with a NULL argument"),
			"gregorio_first_glyph",
			ERROR, 0);
    }
  element = syllable->elements[0];
  while (element)
    {
      if (element->type == GRE_ELEMENT && element->first_glyph)
	{
	  glyph = element->first_glyph;
	  while (glyph)
	    {
	      if (glyph->type == GRE_GLYPH && glyph->first_note)
		{
		  return glyph;
		}
	      glyph = glyph->next;
	    }
	}
      element = element->next;
    }
  return NULL;
}
