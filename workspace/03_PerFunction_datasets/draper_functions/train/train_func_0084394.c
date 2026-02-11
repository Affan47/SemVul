m_emit_impl (pIIR_ReportStatement rs, string &str, RegionStack &rstack, int l)
{

  last_pos_info = emit_posinfo(rs->pos, str, last_pos_info, l);

  str += spaces(l) + "report(";
  if (rs->report_expression != NULL)
    {
      emit_expr (rs->report_expression, str, rstack, DEFAULT);
      str += ",";
    }
  if (rs->severity_expression != NULL)
    emit_expr (rs->severity_expression, str, rstack, DEFAULT);
  else
    str += "0";
  str += ");\n";
}
