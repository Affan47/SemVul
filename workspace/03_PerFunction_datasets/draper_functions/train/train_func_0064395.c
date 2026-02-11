emit_mode_class (void)
{
  int c;
  struct mode_data *m;

  print_decl ("unsigned char", "mode_class", "NUM_MACHINE_MODES");

  for_all_modes (c, m)
    tagged_printf ("%s", mode_class_names[m->cl], m->name);

  print_closer ();
}
