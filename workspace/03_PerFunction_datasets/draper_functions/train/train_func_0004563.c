introspection_callable_call_single_arg (IntrospectionCallable *callable,
                                        gboolean              *called)
{
  IntrospectionCallableInterface *iface;

  g_return_if_fail (INTROSPECTION_IS_CALLABLE (callable));

  iface = INTROSPECTION_CALLABLE_GET_IFACE (callable);
  g_assert (iface->call_single_arg != NULL);

  iface->call_single_arg (callable, called);
}
