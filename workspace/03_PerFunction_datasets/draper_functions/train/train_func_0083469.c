coerce_identity_declaration (NODE_T * p)
{
  if (p != NO_NODE) {
    switch (ATTRIBUTE (p)) {
    case DECLARER:
      {
        coerce_declarer (SUB (p));
        coerce_identity_declaration (NEXT (p));
        break;
      }
    case DEFINING_IDENTIFIER:
      {
        SOID_T q;
        make_soid (&q, STRONG, MOID (p), 0);
        coerce_unit (NEXT_NEXT (p), &q);
        break;
      }
    default:
      {
        coerce_identity_declaration (SUB (p));
        coerce_identity_declaration (NEXT (p));
        break;
      }
    }
  }
}
