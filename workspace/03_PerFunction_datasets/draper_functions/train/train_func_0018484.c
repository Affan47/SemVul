tool_option_free(ToolOption *option)
{
  g_return_if_fail(option);

  g_free(option->name);
  g_free(option->label);
  g_value_unset(option->value);
  g_slice_free(GValue, option->value);
  g_free(option);
}
