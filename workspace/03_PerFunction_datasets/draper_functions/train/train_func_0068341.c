pop_nested_class (void)
{
  tree context = DECL_CONTEXT (TYPE_MAIN_DECL (current_class_type));

  popclass ();
  if (context && CLASS_TYPE_P (context))
    pop_nested_class ();
}
