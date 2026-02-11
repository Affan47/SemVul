_mi_store_var_pack_key(MI_KEYDEF *keyinfo  __attribute__((unused)),
                            register uchar *key_pos,
                            register MI_KEY_PARAM *s_temp)
{
  uint length;
  uchar *start;

  start=key_pos;

  if (s_temp->ref_length)
  {

    store_pack_length(s_temp->pack_marker == 128,key_pos,s_temp->ref_length);

    if (s_temp->ref_length != s_temp->pack_marker)
      store_key_length_inc(key_pos,s_temp->key_length);
  }
  else
  {

    store_pack_length(s_temp->pack_marker == 128,key_pos,s_temp->key_length);
  }
  bmove((uchar*) key_pos,(uchar*) s_temp->key,
        (length=s_temp->totlength-(uint) (key_pos-start)));

  if (!s_temp->next_key_pos)
    return;
  key_pos+=length;

  if (s_temp->prev_length)
  {

    if (s_temp->part_of_prev_key)
    {
      store_pack_length(s_temp->pack_marker == 128,key_pos,
                        s_temp->part_of_prev_key);
      store_key_length_inc(key_pos,s_temp->n_length);
    }
    else
    {
      s_temp->n_length+= s_temp->store_not_null;
      store_pack_length(s_temp->pack_marker == 128,key_pos,
                        s_temp->n_length);
    }
    memcpy(key_pos, s_temp->prev_key, s_temp->prev_length);
  }
  else if (s_temp->n_ref_length)
  {
    store_pack_length(s_temp->pack_marker == 128,key_pos,s_temp->n_ref_length);
    if (s_temp->n_ref_length == s_temp->pack_marker)
      return;
    store_key_length(key_pos,s_temp->n_length);
  }
  else
  {
    s_temp->n_length+= s_temp->store_not_null;
    store_pack_length(s_temp->pack_marker == 128,key_pos,s_temp->n_length);
  }
}
