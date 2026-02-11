DetectPolyobjSectors(void)
{
  int i;
  int hexen_style;


  for (i = 0; i < num_linedefs; i++)
  {
    linedef_t *L = lev_linedefs[i];

    if (L->type == HEXTYPE_POLY_START || L->type == HEXTYPE_POLY_EXPLICIT)
      break;
  }

  if (i == num_linedefs)
  {

    return;
  }


  hexen_style = TRUE;

  for (i = 0; i < num_things; i++)
  {
    thing_t *T = LookupThing(i);

    if (T->type == ZDOOM_PO_SPAWN_TYPE || T->type == ZDOOM_PO_SPAWNCRUSH_TYPE)
    {

      hexen_style = FALSE;
      break;
    }
  }

# if DEBUG_POLYOBJ
  PrintDebug("Using %s style polyobj things\n",
      hexen_style ? "HEXEN" : "ZDOOM");
# endif

  for (i = 0; i < num_things; i++)
  {
    thing_t *T = LookupThing(i);

    float_g x = (float_g) T->x;
    float_g y = (float_g) T->y;


    if (hexen_style)
    {

      if (T->type != PO_SPAWN_TYPE && T->type != PO_SPAWNCRUSH_TYPE)
        continue;
    }
    else
    {

      if (T->type != ZDOOM_PO_SPAWN_TYPE && T->type != ZDOOM_PO_SPAWNCRUSH_TYPE)
        continue;
    }

#   if DEBUG_POLYOBJ
    PrintDebug("Thing %d at (%1.0f,%1.0f) is a polyobj spawner.\n", i, x, y);
#   endif

    MarkPolyobjPoint(x, y);
  }
}
