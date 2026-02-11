cdfg_emit_lit (pIIR_Literal l, string &str)
{
  if (l == NULL)
    str += "1";
  else if (l->is(IR_TEXT_LITERAL))
    str += pIIR_TextLiteral(l)->text.to_chars();
  else if (l->is(IR_INTEGER_LITERAL))
    str += pIIR_IntegerLiteral(l)->text.to_chars();
  else if (l->is(IR_FLOATING_POINT_LITERAL))
    str += pIIR_FloatingPointLiteral(l)->text.to_chars();
  else
    str += "<" + string(l->kind_name()) + ">";
}
