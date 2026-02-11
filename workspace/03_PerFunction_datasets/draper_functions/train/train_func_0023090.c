bind_format_tags_to_tree (NODE_T * p)
{

  for (; p != NO_NODE; FORWARD (p)) {
    if (IS (p, FORMAT_TEXT) && TAX (p) != NO_TAG) {
      NODE (TAX (p)) = p;
    } else if (IS (p, FORMAT_DELIMITER_SYMBOL) && NEXT (p) != NO_NODE && TAX (p) != NO_TAG) {
      NODE (TAX (p)) = p;
    }
    bind_format_tags_to_tree (SUB (p));
  }
}
