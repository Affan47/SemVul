init(int intVars, int boolVars,
                      int setVars, int floatVars) {
    (void) setVars;
    (void) floatVars;

    intVarCount = 0;
    iv = IntVarArray(*this, intVars);
    iv_introduced = std::vector<bool>(2*intVars);
    iv_boolalias = alloc<int>(intVars+(intVars==0?1:0));
    boolVarCount = 0;
    bv = BoolVarArray(*this, boolVars);
    bv_introduced = std::vector<bool>(2*boolVars);
#ifdef GECODE_HAS_SET_VARS
    setVarCount = 0;
    sv = SetVarArray(*this, setVars);
    sv_introduced = std::vector<bool>(2*setVars);
#endif
#ifdef GECODE_HAS_FLOAT_VARS
    floatVarCount = 0;
    fv = FloatVarArray(*this, floatVars);
    fv_introduced = std::vector<bool>(2*floatVars);
#endif
  }
