output_equationWithVariables_sif(ostream& out, short indent_size, short indent_level,
                                           ParameterField* equation_pf,
                                           ParameterField* equation_vars_pf)
{
  const int var_count =  equation_vars_pf->getNofDataStrings();
  char** var_names = equation_vars_pf->getDataStrings();

  for ( int i = 0; i < var_count; i++) {

    LibFront::indent(out, indent_size, indent_level);

    strstream strm;

    strm << equation_pf->getSifName() << " " << var_names[i] << " = " << ends;

    out << strm.str();
    equation_pf->output_sif_type(out);
    equation_pf->output_sif_data(out, indent_size, true, indent_level);

    if ( i < var_count - 1) {
      out << endl;
    }
  }

  return out;
}
