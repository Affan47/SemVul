create_user_defined_type (const char *type_name, struct fileloc *pos)
{
  type_p ty = find_structure (type_name, TYPE_USER_STRUCT);


  ty->kind = TYPE_USER_STRUCT;

  ty->u.s.line = *pos;
  ty->u.s.bitmap = get_lang_bitmap (pos->file);
  do_typedef (type_name, ty, pos);


  char *str = xstrdup (type_name);
  char *open_bracket = strchr (str, '<');
  if (open_bracket)
    {


      char *arg = open_bracket + 1;
      char *type_id = strtok (arg, ",>");
      pair_p fields = 0;
      while (type_id)
	{


	  const char *field_name = xstrdup (type_id);
	  type_p arg_type = resolve_typedef (field_name, pos);
	  fields = create_field_at (fields, arg_type, field_name, 0, pos);
	  type_id = strtok (0, ",>");
	}


      ty->u.s.fields = fields;
    }
  free (str);

  return ty;
}
