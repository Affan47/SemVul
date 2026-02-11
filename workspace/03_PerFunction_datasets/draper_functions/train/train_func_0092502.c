concat(Expressions *udas1, Expressions *udas2)
{
    Expressions *udas;
    if (!udas1 || udas1->dim == 0)
        udas = udas2;
    else if (!udas2 || udas2->dim == 0)
        udas = udas1;
    else
    {


        udas = new Expressions();
        udas->push(new TupleExp(Loc(), udas1));
        udas->push(new TupleExp(Loc(), udas2));
    }
    return udas;
}
