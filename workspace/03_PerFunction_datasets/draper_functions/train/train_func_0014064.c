output_vect (vla_hwint_t vect)
{
  int els_on_line;
  size_t vect_length = vect.length ();
  size_t i;

  els_on_line = 1;
  if (vect_length == 0)
    fputs ("0 /* This is dummy el because the vect is empty */", output_file);
  else
    for (i = 0; i < vect_length; i++)
      {
	fprintf (output_file, "%5ld", (long) vect[i]);
	if (els_on_line == 10)
	  {
	    els_on_line = 0;
	    fputs (",\n", output_file);
	  }
	else if (i < vect_length-1)
	  fputs (", ", output_file);
	els_on_line++;
      }
}
