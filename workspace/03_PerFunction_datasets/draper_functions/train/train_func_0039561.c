lle_X_exit(FunctionType *FT,
                        const std::vector<GenericValue> &Args) {
  TheInterpreter->exitCalled(Args[0]);
  return GenericValue();
}
