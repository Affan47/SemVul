fix_length_and_dec()
{
  decimals=0;
  max_length=3;
  if (args[0]->const_item() && args[1]->type() == FIELD_ITEM)
  {
    Field *field= ((Item_field*) args[1])->field;
    if (field->real_type() == MYSQL_TYPE_SET)
    {
      String *find=args[0]->val_str(&value);
      if (find)
      {

        DBUG_ASSERT(!args[0]->null_value);
	enum_value= find_type(((Field_enum*) field)->typelib,find->ptr(),
			      find->length(), 0);
	enum_bit=0;
	if (enum_value)
	  enum_bit=LL(1) << (enum_value-1);
      }
    }
  }
  agg_arg_charsets_for_comparison(cmp_collation, args, 2);
}
