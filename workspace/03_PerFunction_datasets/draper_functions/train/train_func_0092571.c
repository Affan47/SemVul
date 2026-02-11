print(String *str)
{

  if (str->reserve(2*SP_INSTR_UINT_MAXLEN+14+32))
    return;
  str->qs_append(STRING_WITH_LEN("jump_if_not "));
  str->qs_append(m_dest);
  str->qs_append('(');
  str->qs_append(m_cont_dest);
  str->qs_append(STRING_WITH_LEN(") "));
  m_expr->print(str, QT_ORDINARY);
}
