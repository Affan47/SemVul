mx_stylable_child_notify (ClutterActor *actor,
                          gpointer      flags)
{
  if (MX_IS_STYLABLE (actor))
    mx_stylable_style_changed_internal (MX_STYLABLE (actor),
                                        GPOINTER_TO_INT (flags));
}
