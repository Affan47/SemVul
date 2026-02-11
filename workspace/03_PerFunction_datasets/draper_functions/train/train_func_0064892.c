inf_text_move_operation_need_concurrency_id(InfAdoptedOperation* operation,
                                            InfAdoptedOperation* against)
{
  g_assert(INF_TEXT_IS_MOVE_OPERATION(operation));
  return FALSE;
}
