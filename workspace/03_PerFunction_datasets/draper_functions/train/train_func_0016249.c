ExecutePostLayoutBinding(MCAssembler &Asm) {


  for (MCAssembler::const_iterator i = Asm.begin(), e = Asm.end(); i != e; i++)
    DefineSection(*i);

  for (MCAssembler::const_symbol_iterator i = Asm.symbol_begin(),
                                          e = Asm.symbol_end(); i != e; i++) {
    if (ExportSymbol(*i, Asm))
      DefineSymbol(*i, Asm);
  }
}
