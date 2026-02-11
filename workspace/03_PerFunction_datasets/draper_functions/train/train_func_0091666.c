check_type_int(Exp *e) {
  if(e->type->dimensions || e->type->type != TK_TINT)
    print_error("expression is not an integer", e->line);
}
