setindexsyntax(int&lexpos, int &lineno)
{
    int arrayno, indexarray[mx_array_dim], nindex=0;
    int i;

    lexmovenext(lexpos);

    if (id!=outArray[lexpos])
        outerror(lineno, "id is missing.");
    else
    {
        arrayno=idnosyn++;
        lexmovenext(lexpos);
    }

    for (i = 0; i < mx_array_dim; i++)
       indexarray[i] = 0;

    while (id==outArray[lexpos]&& !endofoutArray)
    {
        if (nindex<mx_array_dim)
        {
            indexarray[nindex]=idnosyn;
        }
        nindex++;
        idnosyn++;
        lexmovenext(lexpos);
    }
    if(nindex>mx_array_dim)
        outerror(lineno,
        "resetindex: Too many indices detected.");


    outerror(lineno, "resetindex not supported anymore.");

    moveoverreturn(lexpos, lineno);

}
