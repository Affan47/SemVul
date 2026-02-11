PrintFst(const FstClass &fst, ostream &ostrm, const string &dest,
              const SymbolTable *isyms,
              const SymbolTable *osyms,
              const SymbolTable *ssyms,
              bool accept, bool show_weight_one) {
  string sep = FLAGS_fst_field_separator.substr(0, 1);
  FstPrinterArgs args(fst, isyms, osyms, ssyms, accept, show_weight_one,
                      &ostrm, dest, sep);
  Apply<Operation<FstPrinterArgs> >("PrintFst", fst.ArcType(), &args);
}
