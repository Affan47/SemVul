operationidsyntax(int &lexpos, int &lineno)
{
    int array1no, array2no, array3no;
    int nindex1, nindex2, nindex3;
    int indexarray1[mx_array_dim], indexarray2[mx_array_dim], indexarray3[mx_array_dim];
    int op;
    int i;

    commonarraysyntax(lexpos, lineno, array1no, nindex1, indexarray1);


    if (addassign==outArray[lexpos]||
        subassign==outArray[lexpos]||
        multassign==outArray[lexpos]||
        divassign==outArray[lexpos])
    {
        if (addassign==outArray[lexpos])
            op=add;
        else if (subassign==outArray[lexpos])
            op=sub;
        else if (multassign==outArray[lexpos])
            op=mult;
        else
            op=divide;
        lexmovenext(lexpos);
        commonarraysyntax(lexpos, lineno, array2no, nindex2, indexarray2);

        array3no=array1no;
        nindex3=nindex1;
        for(i=0;i<nindex3; i++)
            indexarray3[i]=indexarray1[i];
        Instruct.insert(op, array1no, nindex1, indexarray1,
            array3no, nindex3, indexarray3,
            array2no, nindex2, indexarray2);
    }
    else if (assign==outArray[lexpos])
    {
        lexmovenext(lexpos);

        commonarraysyntax(lexpos, lineno, array2no, nindex2, indexarray2);

        if (mult==outArray[lexpos]||
            add==outArray[lexpos]||
            sub==outArray[lexpos]||
            divide==outArray[lexpos]||
            tensor==outArray[lexpos])
        {
            op=outArray[lexpos];
            if (op == divide) op = divide_array;
            lexmovenext(lexpos);

            commonarraysyntax(lexpos, lineno, array3no, nindex3, indexarray3);

            Instruct.insert(op, array1no, nindex1, indexarray1,
                array2no, nindex2, indexarray2,
                array3no, nindex3, indexarray3);
        }
        else
        {
            Instruct.insert(assign, array1no, nindex1, indexarray1,
                array2no, nindex2, indexarray2);
        }

    }
    else
        outerror(lineno,  "= is missing.");

    moveoverreturn(lexpos, lineno);
}
