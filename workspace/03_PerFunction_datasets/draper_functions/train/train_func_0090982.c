Expand (
    int iNumArgs, CPreprocessor::Token *iArgs, Macro *iMacros)
{
    Expanding = true;

    CPreprocessor cpp;
    cpp.MacroList = iMacros;


    int i;
    for (i = 0; i < iNumArgs; i++)
        cpp.Define (Args [i].String, Args [i].Length,
                    iArgs [i].String, iArgs [i].Length);

    for (; i < NumArgs; i++)
        cpp.Define (Args [i].String, Args [i].Length, "", 0);


    Token xt = cpp.Parse (Value);

    Expanding = false;


    for (int j = NumArgs - 1; j >= 0; j--)
        cpp.Undef (Args [j].String, Args [j].Length);

    cpp.MacroList = NULL;

    return xt;
}
