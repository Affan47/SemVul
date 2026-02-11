create_symbols(void)
{

  if(verbose)
    cout << "creating f884 symbols\n";

  P16F88x::create_symbols();

  addSymbol(m_portd);
  addSymbol(m_trisd);

}
