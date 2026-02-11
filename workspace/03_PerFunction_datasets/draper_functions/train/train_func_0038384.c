is_unit_being_refueled(const struct unit *punit)
{
  return (unit_transported(punit)
          || tile_city(unit_tile(punit))
          || tile_has_native_base(unit_tile(punit),
                                  unit_type(punit)));
}
