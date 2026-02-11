visu_ui_main_class_getRememberPosition()
{
  g_return_val_if_fail(my_class, PARAMETER_GTKMAIN_REMEMBER_DEFAULT);
  return my_class->rememberWindowPosition;
}
