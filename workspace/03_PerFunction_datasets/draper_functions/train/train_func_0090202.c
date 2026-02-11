sprite_types_setup()
{
  int i;
  sprite_types_register();
  for (i=0;i<nr_sprite_types;i++)
    {
      ndef(&sprite_types,sprite_types_list[i]->name,
	   sprite_types_list[i]);
    }
  return 0;
}
