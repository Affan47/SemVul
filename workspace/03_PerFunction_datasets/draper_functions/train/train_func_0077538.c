identification_output (struct localedef_t *locale,
		       const struct charmap_t *charmap,
		       const char *output_path)
{
  struct locale_identification_t *identification
    = locale->categories[LC_IDENTIFICATION].identification;
  struct locale_file file;
  size_t num;

  init_locale_data (&file, _NL_ITEM_INDEX (_NL_NUM_LC_IDENTIFICATION));
  add_locale_string (&file, identification->title);
  add_locale_string (&file, identification->source);
  add_locale_string (&file, identification->address);
  add_locale_string (&file, identification->contact);
  add_locale_string (&file, identification->email);
  add_locale_string (&file, identification->tel);
  add_locale_string (&file, identification->fax);
  add_locale_string (&file, identification->language);
  add_locale_string (&file, identification->territory);
  add_locale_string (&file, identification->audience);
  add_locale_string (&file, identification->application);
  add_locale_string (&file, identification->abbreviation);
  add_locale_string (&file, identification->revision);
  add_locale_string (&file, identification->date);
  start_locale_structure (&file);
  for (num = 0; num < __LC_LAST; ++num)
    if (num != LC_ALL)
      add_locale_string (&file, identification->category[num]);
  end_locale_structure (&file);
  add_locale_string (&file, charmap->code_set_name);
  write_locale_data (output_path, LC_IDENTIFICATION, "LC_IDENTIFICATION",
		     &file);
}
