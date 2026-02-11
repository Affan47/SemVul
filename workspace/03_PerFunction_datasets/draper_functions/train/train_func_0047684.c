opcode_bit_cmp (opcode_bits *l, opcode_bits *r)
{
  if (l == NULL && r == NULL)
    return 0;
  if (l == NULL)
    return -1;
  if (r == NULL)
    return +1;

  if (l->field->word_nr < r->field->word_nr)
    return +1;
  if (l->field->word_nr > r->field->word_nr)
    return -1;

  if (l->first < r->first)
    return +1;
  if (l->first > r->first)
    return -1;

  if (l->last < r->last)
    return +1;
  if (l->last > r->last)
    return -1;

  if (l->value < r->value)
    return -1;
  if (l->value > r->value)
    return 1;
  return 0;
}
