scalardecsyntax(int &lexpos, int &lineno)
{
    int indexnameno=0;
    double value1=0;
    int negtive=0;

    lexmovenext(lexpos);
    if (id!=outArray[lexpos])
        outerror(lineno, "idname is missing.");
    else
    {
        indexnameno=idnosyn++;
        lexmovenext(lexpos);
    }

    if (assign==outArray[lexpos])
    {
        lexmovenext(lexpos);

        if (sub==outArray[lexpos])
        {
            negtive=1;
            lexmovenext(lexpos);
        }

        if (fconst==outArray[lexpos])
        {
            value1=floatconst[floatnosyn];
            if (negtive)
                value1=-value1;
            floatnosyn++;
            lexmovenext(lexpos);
        }
        else if (iconst==outArray[lexpos])
        {
            lexmovenext(lexpos);
            value1=double(intconst[intnosyn]);
            if (negtive)
                value1=-value1;
            intnosyn++;
        }
        else
            outerror(lineno, "value is missing.");
    }

    QCArray.insertscalar(indexnameno, value1);

    moveoverreturn (lexpos, lineno);
}
