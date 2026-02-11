tile_has_claimable_base(const struct tile *ptile,
                             const struct unit_type *punittype)
{
  base_type_iterate(pbase) {
    if (tile_has_base(ptile, pbase)
        && territory_claiming_base(pbase)
        && is_native_base_to_uclass(pbase, utype_class(punittype))) {
      return TRUE;
    }
  } base_type_iterate_end;

  return FALSE;
}
