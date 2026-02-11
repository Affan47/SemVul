inf_text_move_operation_get_concurrency_id(InfAdoptedOperation* operation,
                                           InfAdoptedOperation* against)
{
  g_assert(INF_TEXT_IS_MOVE_OPERATION(operation));
  _inf_adopted_concurrency_warning(INF_TEXT_TYPE_MOVE_OPERATION);
  return INF_ADOPTED_CONCURRENCY_NONE;
}
