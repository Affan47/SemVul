Fstkempty()
{
    struct stack *sptr;

    if(*FLAGPTR(argStkPtr) != fSTACK) {
        error(emptysym,err_stkv,voidsym);
        return(brkerr());
    }
    sptr = (struct stack *)TAddress(argStkPtr);
    return(sptr->page == nullsym ? true : false);
}
