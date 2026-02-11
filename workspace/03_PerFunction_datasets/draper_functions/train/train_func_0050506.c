bind_identifier_tag_to_symbol_table (NODE_T * p)
{
  for (; p != NO_NODE; FORWARD (p)) {
    bind_identifier_tag_to_symbol_table (SUB (p));
    if (is_one_of (p, IDENTIFIER, DEFINING_IDENTIFIER, STOP)) {
      int att = first_tag_global (TABLE (p), NSYMBOL (p));
      TAG_T *z;
      if (att == STOP) {
        if ((z = bind_lengthety_identifier (NSYMBOL (p))) != NO_TAG) {
          MOID (p) = MOID (z);


        }
        TAX (p) = z;
      } else {
        z = find_tag_global (TABLE (p), att, NSYMBOL (p));
        if (att == IDENTIFIER && z != NO_TAG) {
          MOID (p) = MOID (z);
        } else if (att == LABEL && z != NO_TAG) {
          ;
        } else if ((z = bind_lengthety_identifier (NSYMBOL (p))) != NO_TAG) {
          MOID (p) = MOID (z);
        } else {
          diagnostic_node (A68_ERROR, p, ERROR_UNDECLARED_TAG);
          z = add_tag (TABLE (p), IDENTIFIER, p, MODE (ERROR), NORMAL_IDENTIFIER);
          MOID (p) = MODE (ERROR);
        }
        TAX (p) = z;
        if (IS (p, DEFINING_IDENTIFIER)) {
          NODE (z) = p;
        }
      }
    }
  }
}
