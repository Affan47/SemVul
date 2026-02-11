AInvRat (
    Obj                 op )
{
    Obj                 res;
    Obj                 tmp;
    CHECK_RAT(op);
    res = NewBag( T_RAT, 2 * sizeof(Obj) );
    tmp = AINV( NUM_RAT(op) );
    NUM_RAT(res) = tmp;
    DEN_RAT(res) = DEN_RAT(op);
    CHANGED_BAG(res);
    CHECK_RAT(res);
    return res;
}
