difference_lagrangian()
{ REAL sum;
  body_id b_id;
  struct gen_quant *q;
  int k;

  sum = web.total_energy;
  FOR_ALL_BODIES(b_id)
    if ( get_battr(b_id) & FIXEDVOL )
      sum -= get_body_pressure(b_id)*get_body_volume(b_id);
  for ( k = 0 ; k < gen_quant_count ; k++ )
  { q = GEN_QUANT(k);
    if ( q->flags & Q_FIXED )
      sum -= q->pressure*q->value;
  }
  return sum;
}
