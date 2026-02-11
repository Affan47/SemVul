embPropTransversion(char base1, char base2)
{
    AjBool bu1;
    AjBool bu2;
    AjBool by1;
    AjBool by2;

    bu1 = embPropPurine(base1);
    bu2 = embPropPurine(base2);

    by1 = embPropPyrimidine(base1);
    by2 = embPropPyrimidine(base2);

    ajDebug("base1 py = %b, pu = %b", bu1, by1);
    ajDebug("base2 py = %b, pu = %b", bu2, by2);


    if(!bu1 && !by1)
	return ajFalse;

    if(!bu2 && !by2)
	return ajFalse;

    ajDebug("embPropTransversion result = %d", (bu1 != bu2));

    return (bu1 != bu2);
}
