free_vars( VariableList &context, VariableList &vars ) const
{
  for( FormulaList::const_iterator fi = conjuncts_.begin(); fi != conjuncts_.end(); ++fi )
    (*fi)->free_vars( context, vars );
}
