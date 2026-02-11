inf_text_delete_operation_transform_delete(InfTextDeleteOperation* operation,
                                           InfTextDeleteOperation* against,
                                           InfAdoptedConcurrencyId cid)
{
  InfTextDeleteOperationIface* iface;
  guint own_pos;
  guint own_len;
  guint other_pos;
  guint other_len;

  g_return_val_if_fail(INF_TEXT_IS_DELETE_OPERATION(operation), NULL);
  g_return_val_if_fail(INF_TEXT_IS_DELETE_OPERATION(against), NULL);

  iface = INF_TEXT_DELETE_OPERATION_GET_IFACE(operation);
  g_return_val_if_fail(iface->transform_position != NULL, NULL);
  g_return_val_if_fail(iface->transform_overlap != NULL, NULL);

  own_pos = inf_text_delete_operation_get_position(operation);
  own_len = inf_text_delete_operation_get_length(operation);
  other_pos = inf_text_delete_operation_get_position(against);
  other_len = inf_text_delete_operation_get_length(against);

  if(own_pos + own_len <= other_pos)
  {
    return inf_adopted_operation_copy(INF_ADOPTED_OPERATION(operation));
  }
  else if(own_pos >= other_pos + other_len)
  {
    return INF_ADOPTED_OPERATION(
      iface->transform_position(operation, own_pos - other_len)
    );
  }

  else if(other_pos <= own_pos && other_pos + other_len >= own_pos + own_len)
  {
    return INF_ADOPTED_OPERATION(
      iface->transform_overlap(
        operation,
        against,
        other_pos,
        0,
        own_pos - other_pos,
        own_len
      )
    );
  }
  else if(other_pos <= own_pos && other_pos + other_len < own_pos + own_len)
  {
    return INF_ADOPTED_OPERATION(
      iface->transform_overlap(
        operation,
        against,
        other_pos,
        0,
        own_pos - other_pos,
        other_pos + other_len - own_pos
      )
    );
  }
  else if(other_pos > own_pos && other_pos + other_len >= own_pos + own_len)
  {
    return INF_ADOPTED_OPERATION(
      iface->transform_overlap(
        operation,
        against,
        own_pos,
        other_pos - own_pos,
        0,
        own_pos + own_len - other_pos
      )
    );
  }
  else
  {
    return INF_ADOPTED_OPERATION(
      iface->transform_overlap(
        operation,
        against,
        own_pos,
        other_pos - own_pos,
        0,
        other_len
      )
    );
  }
}
