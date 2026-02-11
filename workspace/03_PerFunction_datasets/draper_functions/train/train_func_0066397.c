writeOutput(ostream &output, ExprNodeOutputType output_type, const temporary_terms_t &temporary_terms) const
{
  deriv_node_temp_terms_t tef_terms;
  writeOutput(output, output_type, temporary_terms, tef_terms);
}
