operation_is_completed (guint operation_id)
{
  struct OperationState *op_state;

  op_state = grl_operation_get_private_data (operation_id);

  return !op_state || op_state->completed;
}
