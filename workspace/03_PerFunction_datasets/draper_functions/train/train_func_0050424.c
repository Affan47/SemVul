records_in_range(uint inx, key_range *min_key,
                                  key_range *max_key)
{
  KEY *key=table->key_info+inx;
  if (key->algorithm == HA_KEY_ALG_BTREE)
    return hp_rb_records_in_range(file, inx, min_key, max_key);

  if (!min_key || !max_key ||
      min_key->length != max_key->length ||
      min_key->length != key->key_length ||
      min_key->flag != HA_READ_KEY_EXACT ||
      max_key->flag != HA_READ_AFTER_KEY)
    return HA_POS_ERROR;

  if (stats.records <= 1)
    return stats.records;


  DBUG_ASSERT(key_stat_version == file->s->key_stat_version);
  return key->rec_per_key[key->key_parts-1];
}
