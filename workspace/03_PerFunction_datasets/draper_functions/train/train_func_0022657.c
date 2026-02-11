gabc_write_gregorio_elements (FILE *
					  f, gregorio_element * element)
{
  while (element)
    {
      gabc_write_gregorio_element (f, element);

      if (element->type != GRE_END_OF_LINE
	  && (element->type != GRE_SPACE
	      || (element->type == GRE_SPACE
		  && element->element_type == SP_NEUMATIC_CUT))
	  && element->next
	  && element->next->type == GRE_ELEMENT)
	{
	  fprintf (f, "/");
	}
      element = element->next;
    }
}
