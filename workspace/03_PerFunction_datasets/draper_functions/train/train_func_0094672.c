gregorio_free_score (gregorio_score * score)
{
  if (!score)
    {
      gregorio_message (_("function called with NULL argument"),
			   "free_one_syllable", WARNING, 0);
      return;
    }
  gregorio_free_syllables (&(score->first_syllable),
			      score->number_of_voices);
  gregorio_free_score_infos (score);
  free (score);
}
