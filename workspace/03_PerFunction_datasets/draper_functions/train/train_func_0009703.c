render(render_guts_t* guts, int indentation) const {
  rope_t ret;
  bool need_space = false;
  switch(this->op) {
    case DELETE:
      ret += "delete";
      need_space = true;
      break;
    case VOID:
      ret += "void";
      need_space = true;
      break;
    case TYPEOF:
      ret += "typeof";
      need_space = true;
      break;
    case INCR_UNARY:
      ret += "++";
      break;
    case DECR_UNARY:
      ret += "--";
      break;
    case PLUS_UNARY:
      ret += "+";
      break;
    case MINUS_UNARY:
      ret += "-";
      break;
    case BIT_NOT_UNARY:
      ret += "~";
      break;
    case NOT_UNARY:
      ret += "!";
      break;
  }
  if (need_space && dynamic_cast<NodeParenthetical*>(this->_childNodes.front()) == NULL) {
    ret += " ";
  }
  ret += this->_childNodes.front()->render(guts, indentation);
  return ret;
}
