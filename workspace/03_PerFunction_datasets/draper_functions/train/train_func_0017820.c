enhancer_helper_check (G_GNUC_UNUSED GmTextBufferEnhancerHelper* self,
		       const gchar* full_text,
		       gint from,
		       gint* start,
		       gint* length)
{
  const gchar **smileys = gm_get_smileys ();
  gint smiley = 0;
  gint best_start = 0;
  gint best_smiley = -1;
  char* found = NULL;
  gint found_start = 0;


  for (smiley = 0;
       smileys[smiley] != NULL;
       smiley = smiley + 2) {

    found = strstr (full_text + from, smileys[smiley]);
    if (found != NULL) {

      found_start = found - full_text;
      if ((best_smiley == -1)
          || (found_start < best_start)
	  || ((found_start == best_start)
	      && (strlen (smileys[smiley]) > strlen (smileys[best_smiley])))) {

	best_smiley = smiley;
	best_start = found_start;
      }
    }
  }


  if (best_smiley != -1) {

    *start = best_start;
    *length = strlen (smileys[best_smiley]);
  } else
    *length = 0;
}
