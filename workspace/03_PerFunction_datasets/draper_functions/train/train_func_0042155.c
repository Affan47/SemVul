read_rtx (const char *rtx_name, rtx *x)
{
  static rtx queue_head;
  struct map_value *mode_maps;
  struct iterator_traverse_data mtd;


  if (queue_head == 0)
    {
      initialize_iterators ();
      queue_head = rtx_alloc (EXPR_LIST);
    }


  if (strcmp (rtx_name, "define_conditions") == 0)
    {
      read_conditions ();
      return false;
    }
  if (strcmp (rtx_name, "define_mode_attr") == 0)
    {
      read_mapping (&modes, modes.attrs);
      return false;
    }
  if (strcmp (rtx_name, "define_mode_iterator") == 0)
    {
      read_mapping (&modes, modes.iterators);
      return false;
    }
  if (strcmp (rtx_name, "define_code_attr") == 0)
    {
      read_mapping (&codes, codes.attrs);
      return false;
    }
  if (strcmp (rtx_name, "define_code_iterator") == 0)
    {
      check_code_iterator (read_mapping (&codes, codes.iterators));
      return false;
    }

  mode_maps = 0;
  XEXP (queue_head, 0) = read_rtx_code (rtx_name, &mode_maps);
  XEXP (queue_head, 1) = 0;

  mtd.queue = queue_head;
  mtd.mode_maps = mode_maps;
  mtd.unknown_mode_attr = mode_maps ? mode_maps->string : NULL;
  htab_traverse (modes.iterators, apply_iterator_traverse, &mtd);
  htab_traverse (codes.iterators, apply_iterator_traverse, &mtd);
  if (mtd.unknown_mode_attr)
    fatal_with_file_and_line ("undefined attribute '%s' used for mode",
			      mtd.unknown_mode_attr);

  *x = queue_head;
  return true;
}
