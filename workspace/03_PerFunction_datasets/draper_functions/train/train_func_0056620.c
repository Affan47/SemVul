addExpectationAuxiliaryVar(int information_set, int index) throw (FrozenException)
{
  ostringstream varname;
  int symb_id;

  varname << "AUX_EXPECT_" << (information_set < 0 ? "LAG" : "LEAD") << "_"
          << abs(information_set) << "_" << index;

  try
    {
      symb_id = addSymbol(varname.str(), eEndogenous);
    }
  catch (AlreadyDeclaredException &e)
    {
      cerr << "ERROR: you should rename your variable called " << varname.str() << ", this name is internally used by Dynare" << endl;
      exit(EXIT_FAILURE);
    }

  aux_vars.push_back(AuxVarInfo(symb_id, avExpectation, 0, 0, 0));

  return symb_id;
}
