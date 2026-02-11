hastab_init ()
{
  hastab = (struct tab *) callocx (SIZE_HAS, sizeof (struct tab));
  if (NULL == hastab)
    {
      error_message (4000);
      return (0);
    }
#ifdef DEBUG
  printfx ("Hash table allocated\n\n");
#endif

  return 1;
}
