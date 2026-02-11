add_zone(zone *zn, int elt)
{
  if (((zn->bits[elt >> 5] >> (elt & 31)) & 1) == 0) {
    zn->bits[elt >> 5] |= (1 << (elt & 31));
    zn->array[0]++;
    zn->array[zn->array[0]] = elt;
  }
}
