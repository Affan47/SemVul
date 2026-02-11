inf_adopted_operation_need_concurrency_id(InfAdoptedOperation* operation,
                                          InfAdoptedOperation* against)
{
  InfAdoptedOperationIface* iface;

  g_return_val_if_fail(INF_ADOPTED_IS_OPERATION(operation), FALSE);
  g_return_val_if_fail(INF_ADOPTED_IS_OPERATION(against), FALSE);

  iface = INF_ADOPTED_OPERATION_GET_IFACE(operation);
  g_assert(iface->need_concurrency_id != NULL);

  return iface->need_concurrency_id(operation, against);
}
