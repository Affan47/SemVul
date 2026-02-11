insn_field_type_to_str (insn_field_type type)
{
  switch (type)
    {
    case insn_field_invalid:
      ASSERT (0);
      return "(invalid)";
    case insn_field_int:
      return "int";
    case insn_field_reserved:
      return "reserved";
    case insn_field_wild:
      return "wild";
    case insn_field_string:
      return "string";
    }
  ERROR ("bad switch");
  return 0;
}
