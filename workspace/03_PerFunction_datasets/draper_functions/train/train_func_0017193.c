objbind_set_modified_value(struct objbind *ob,
                                       struct objprop *op,
                                       struct propval *pv)
{
  struct propstate *ps;
  bool equal;
  struct propval *pv_old, *pv_copy;
  enum object_property_ids propid;

  if (!ob || !op) {
    return;
  }

  propid = objprop_get_id(op);

  pv_old = objbind_get_value_from_object(ob, op);
  if (!pv_old) {
    return;
  }

  equal = propval_equal(pv, pv_old);
  propval_free(pv_old);

  if (equal) {
    objbind_clear_modified_value(ob, op);
    return;
  }

  pv_copy = propval_copy(pv);

  if (propstate_hash_lookup(ob->propstate_table, propid, &ps)) {
    propstate_set_value(ps, pv_copy);
  } else {
    ps = propstate_new(op, pv_copy);
    propstate_hash_insert(ob->propstate_table, propid, ps);
  }
}
