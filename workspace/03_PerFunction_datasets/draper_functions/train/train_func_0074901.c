GetSidedefs(void)
{
  int i, count=-1;
  raw_sidedef_t *raw;
  lump_t *lump = FindLevelLump("SIDEDEFS");

  if (lump)
    count = lump->length / sizeof(raw_sidedef_t);

  if (!lump || count == 0)
    FatalError("Couldn't find any Sidedefs");

  DisplayTicker();

# if DEBUG_LOAD
  PrintDebug("GetSidedefs: num = %d\n", count);
# endif

  raw = (raw_sidedef_t *) lump->data;

  for (i=0; i < count; i++, raw++)
  {
    sidedef_t *side = NewSidedef();

    side->sector = (SINT16(raw->sector) == -1) ? NULL :
        LookupSector(UINT16(raw->sector));

    if (side->sector)
      side->sector->ref_count++;

    side->x_offset = SINT16(raw->x_offset);
    side->y_offset = SINT16(raw->y_offset);

    memcpy(side->upper_tex, raw->upper_tex, sizeof(side->upper_tex));
    memcpy(side->lower_tex, raw->lower_tex, sizeof(side->lower_tex));
    memcpy(side->mid_tex,   raw->mid_tex,   sizeof(side->mid_tex));


    side->index = i;
  }
}
