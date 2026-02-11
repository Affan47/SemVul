push_cx_call_context (tree call)
{
  ++call_stack_tick;
  if (!EXPR_HAS_LOCATION (call))
    SET_EXPR_LOCATION (call, input_location);
  call_stack.safe_push (call);
  if (call_stack.length () > (unsigned) max_constexpr_depth)
    return false;
  return true;
}
