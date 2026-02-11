set_operation_symbol(char *operation, char *symbol)
{
  if (str_ident(operation, "true"))
    True_sym = symbol;
  else if (str_ident(operation, "false"))
    False_sym = symbol;
  else if (str_ident(operation, "conjunction"))
    And_sym = symbol;
  else if (str_ident(operation, "disjunction"))
    Or_sym = symbol;
  else if (str_ident(operation, "negation"))
    Not_sym = symbol;
  else if (str_ident(operation, "implication"))
    Imp_sym = symbol;
  else if (str_ident(operation, "backward_implication"))
    Impby_sym = symbol;
  else if (str_ident(operation, "equivalence"))
    Iff_sym = symbol;
  else if (str_ident(operation, "universal_quantification"))
    All_sym = symbol;
  else if (str_ident(operation, "existential_quantification"))
    Exists_sym = symbol;
  else if (str_ident(operation, "quantification"))
    Quant_sym = symbol;
  else if (str_ident(operation, "attribute"))
    Attrib_sym = symbol;
  else if (str_ident(operation, "equality"))
    Eq_sym = symbol;
  else if (str_ident(operation, "negated_equality"))
    Neq_sym = symbol;
  else {
    printf("The unknown operation is %s\n", operation);
    fatal_error("set_operation_symbol, unknown operation");
  }
}
