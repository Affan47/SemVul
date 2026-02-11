ifsyntax(int &lexpos, int &lineno)
{
    int stackno;
    int insif, insfalse, insend;

    lexmovenext(lexpos);

    stackno=conditionsyntax(lexpos, lineno);
    insif=Instruct.insertif(iff, stackno);

    moveoverreturn(lexpos, lineno);

    while (IsInstruction(lexpos))
    {
        instructionsyntax(lexpos, lineno);
    }

    if (elsee==outArray[lexpos])
    {
        lexmovenext(lexpos);
        moveoverreturn(lexpos, lineno);

        insfalse=Instruct.insertif(elsee, 0);
        Instruct.reinsert(insif, insfalse+1);

        while (IsInstruction(lexpos))
        {
            instructionsyntax(lexpos, lineno);
        }
        insend=Instruct.getinsno();
        Instruct.reinsert(insfalse, insend);
    }
    else
    {
        insend=Instruct.getinsno();
        Instruct.reinsert(insif, insend);
    }

    if (endiff!=outArray[lexpos])
    {
        outerror(lineno, "endif missing.");
    }
    else
    {
        lexmovenext(lexpos);
        moveoverreturn(lexpos, lineno);
    }
}
