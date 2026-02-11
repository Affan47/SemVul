m_emit_expr (pIIR_AccessReference aor, string &str, RegionStack &rstack, id_type t)
{
  str += "deref<" + qid(aor->subtype, rstack, TYPE) + " >(";
  emit_expr (aor->access, str, rstack, t);
  str += ")";

  return false;
}
