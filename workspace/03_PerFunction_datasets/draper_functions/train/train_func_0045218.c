returnsilsyntax(int &lexpos, int &lineno)
{
    int variableno=0;
    if (returncount==-1)
        outerror(lineno, "return cannot be used in the main part of sial.");

    if (returnsil==outArray[lexpos])
    {
        Instruct.insert (endproc, variableno);
        lexmovenext(lexpos);
        moveoverreturn(lexpos, lineno);

    }
    else
        outerror(lineno, "unknown error in returnsilsyntax.");
}
