is_key_scan_ror(PARAM *param, uint keynr, uint8 nparts)
{
  KEY *table_key= param->table->key_info + keynr;
  KEY_PART_INFO *key_part= table_key->key_part + nparts;
  KEY_PART_INFO *key_part_end= (table_key->key_part +
                                table_key->key_parts);
  uint pk_number;

  if (key_part == key_part_end)
    return TRUE;
  pk_number= param->table->s->primary_key;
  if (!param->table->file->primary_key_is_clustered() || pk_number == MAX_KEY)
    return FALSE;

  KEY_PART_INFO *pk_part= param->table->key_info[pk_number].key_part;
  KEY_PART_INFO *pk_part_end= pk_part +
                              param->table->key_info[pk_number].key_parts;
  for (;(key_part!=key_part_end) && (pk_part != pk_part_end);
       ++key_part, ++pk_part)
  {
    if ((key_part->field != pk_part->field) ||
        (key_part->length != pk_part->length))
      return FALSE;
  }
  return (key_part == key_part_end);
}
