connection_or_is_better(time_t now,
                        const or_connection_t *a,
                        const or_connection_t *b,
                        int forgive_new_connections)
{
  int newer;


#define NEW_CONN_GRACE_PERIOD (15*60)

  if (b->is_canonical && !a->is_canonical)
    return 0;


  newer = b->_base.timestamp_created < a->_base.timestamp_created;

  if (

      (!b->is_canonical && a->is_canonical) ||

      (b->n_circuits && a->n_circuits && newer) ||

      (!b->n_circuits && !a->n_circuits && newer))
    return 1;


  if (!b->n_circuits && a->n_circuits) {

    if (forgive_new_connections &&
        now < b->_base.timestamp_created + NEW_CONN_GRACE_PERIOD)
      return 0;
    else
      return 1;
  }

  return 0;
}
