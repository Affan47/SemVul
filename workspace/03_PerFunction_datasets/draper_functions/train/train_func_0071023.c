makeSinTable (void)
{
  e_int32 i;

  for (i = 0; i < PG_WIDTH / 4; i++)
  {
    fullsintable[i] = (e_uint32) lin2db (sin (2.0 * PI * i / PG_WIDTH) );
  }

  for (i = 0; i < PG_WIDTH / 4; i++)
  {
    fullsintable[PG_WIDTH / 2 - 1 - i] = fullsintable[i];
  }

  for (i = 0; i < PG_WIDTH / 2; i++)
  {
    fullsintable[PG_WIDTH / 2 + i] = (e_uint32) (DB_MUTE + DB_MUTE + fullsintable[i]);
  }

  for (i = 0; i < PG_WIDTH / 2; i++)
    halfsintable[i] = fullsintable[i];
  for (i = PG_WIDTH / 2; i < PG_WIDTH; i++)
    halfsintable[i] = fullsintable[0];
}
