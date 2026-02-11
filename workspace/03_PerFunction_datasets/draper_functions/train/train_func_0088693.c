most_shallow_ocean(void)
{
  bool oceans = FALSE;
  struct terrain *shallow = NULL;

  terrain_type_iterate(pterr) {
    if (is_ocean(pterr)) {
      if (!oceans && !terrain_has_flag(pterr, TER_FRESHWATER)) {

        oceans = TRUE;
        shallow = pterr;
      } else if (!shallow
                 || pterr->property[MG_OCEAN_DEPTH] <
                    shallow->property[MG_OCEAN_DEPTH]) {
        shallow = pterr;
      }
    }
  } terrain_type_iterate_end;

  return shallow;
}
