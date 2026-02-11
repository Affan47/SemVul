complex_fun( EnvT* e)
{
  if (e->KeywordSet("DOUBLE")) {
    return complex_fun_template< DComplexDblGDL, DComplexDbl, DDoubleGDL>( e);
  } else {
    return complex_fun_template< DComplexGDL, DComplex, DFloatGDL>( e);
  }
}
