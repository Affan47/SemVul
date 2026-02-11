operator==(const Key_part_spec& other) const
{
  return length == other.length &&
         !my_strcasecmp(system_charset_info, field_name.str,
                        other.field_name.str);
}
