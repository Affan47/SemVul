gd_stack_add_named (GdStack    *stack,
                    GtkWidget  *child,
                    const char *name)
{
  g_return_if_fail (GD_IS_STACK (stack));
  g_return_if_fail (GTK_IS_WIDGET (child));

  gtk_container_add_with_properties (GTK_CONTAINER (stack),
                                     child,
                                     "name", name,
                                     NULL);
}
