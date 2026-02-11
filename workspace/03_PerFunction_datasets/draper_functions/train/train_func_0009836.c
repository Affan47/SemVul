gregorio_free_one_syllable (gregorio_syllable ** syllable,
			       int number_of_voices)
{
  int i;
  gregorio_syllable *next;
  if (!syllable || !*syllable)
    {
      gregorio_message (_("function called with NULL argument"),
			   "free_one_syllable", WARNING, 0);
      return;
    }
  for (i = 0; i < number_of_voices; i++)
    {
      gregorio_free_elements ((struct gregorio_element **)
				 &((*syllable)->elements[i]));
    }
  if ((*syllable)->text)
    {
      gregorio_free_characters ((*syllable)->text);
    }
  if ((*syllable)->translation)
    {
      gregorio_free_characters ((*syllable)->translation);
    }
  free((*syllable)->abovelinestext);
  next = (*syllable)->next_syllable;
  free ((*syllable)->elements);
  free (*syllable);
  *syllable = next;
}
