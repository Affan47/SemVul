push_lang_context (tree name)
{
  vec_safe_push (current_lang_base, current_lang_name);

  if (name == lang_name_cplusplus)
    {
      current_lang_name = name;
    }
  else if (name == lang_name_java)
    {
      current_lang_name = name;


      DECL_IGNORED_P (TYPE_NAME (java_byte_type_node)) = 0;
      DECL_IGNORED_P (TYPE_NAME (java_short_type_node)) = 0;
      DECL_IGNORED_P (TYPE_NAME (java_int_type_node)) = 0;
      DECL_IGNORED_P (TYPE_NAME (java_long_type_node)) = 0;
      DECL_IGNORED_P (TYPE_NAME (java_float_type_node)) = 0;
      DECL_IGNORED_P (TYPE_NAME (java_double_type_node)) = 0;
      DECL_IGNORED_P (TYPE_NAME (java_char_type_node)) = 0;
      DECL_IGNORED_P (TYPE_NAME (java_boolean_type_node)) = 0;
    }
  else if (name == lang_name_c)
    {
      current_lang_name = name;
    }
  else
    error ("language string %<\"%E\"%> not recognized", name);
}
