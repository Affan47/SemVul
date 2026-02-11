compare_tile_type_by_stat(const void *va, const void *vb)
{
  struct cm_tile_type * const *a = va;
  struct cm_tile_type * const *b = vb;

  if (*a == *b) {
    return 0;
  }


  double valuea = (*a)->production[compare_key] +
                    compare_key_trade_bonus * (*a)->production[O_TRADE];
  double valueb = (*b)->production[compare_key] +
                    compare_key_trade_bonus * (*b)->production[O_TRADE];


  if (valuea != valueb) {

    return valueb - valuea;
  }

  return compare_tile_type_by_lattice_order(*a, *b);
}
