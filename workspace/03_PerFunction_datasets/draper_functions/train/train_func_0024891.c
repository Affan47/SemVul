mri_alias (const char *want, const char *is, int isn)
{
  if (!is)
    {
      char buf[20];


      sprintf (buf, "%d", isn);

      is = xstrdup (buf);

      if (is == NULL)
	abort ();
    }

  mri_add_to_list (&alias, is, 0, want, 0, 0);
}
