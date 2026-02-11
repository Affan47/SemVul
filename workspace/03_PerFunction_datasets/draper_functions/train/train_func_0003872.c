createPrintFunctionPass(const std::string &Banner,
                                            llvm::raw_ostream *OS,
                                            bool DeleteStream) {
  return new PrintFunctionPass(Banner, OS, DeleteStream);
}
