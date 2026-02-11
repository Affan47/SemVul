part_nexttype(part_t *part, u_int parn, ptyp_t current, int dir)
{
  static ptyp_t types[] = { ptyp_linux_swap, ptyp_linux_native, ptyp_filecore };
  ptyp_t ptype;
  int i;
#define NR_TYPES (sizeof(types)/sizeof(ptyp_t))

  if (part->scheme->nexttype)
    ptype = part->scheme->nexttype(part, parn, current, dir);
  else {
    for(i = 0; i < NR_TYPES; i++)
      if (types[i] == current)
        break;

    if (types[i] == current) {
      i += dir;

      if (i < 0)
        i = 0;

      if (i >= NR_TYPES)
       i = NR_TYPES - 1;
    }

    ptype = types[i];
  }

  return ptype;
}
