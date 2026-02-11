construct()
{
    cout << "creating 16bit processor construct\n";

  _16bit_processor *p = new _16bit_processor;

  if(verbose)
    cout << " 18c242 construct\n";

  p->create();
  p->create_invalid_registers();
  p->create_symbols();
  p->name_str = "generic 16bit processor";
  globalSymbolTable().addModule(p);

  return p;


}
