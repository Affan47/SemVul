dopayobj(struct monst *shkp,
         struct bill_x *bp,
         struct obj **obj_p,
         int which,
         bool itemize)
{
    struct obj *obj = *obj_p;
    long ltmp, quan, save_quan;
    int buy;
    bool stashed_gold = (hidden_gold() > 0L),
         consumed = (which == 0);

    if(!obj->unpaid && !bp->useup){
        impossible("Paid object on bill??");
        return PAY_BUY;
    }
    if(itemize && u.ugold + ESHK(shkp)->credit == 0L){
        You("%shave no money or credit left.",
            stashed_gold ? "seem to " : "");
        return PAY_BROKE;
    }


    save_quan = obj->quan;
    if (consumed)
    {

        quan = bp->bquan;
        if (quan > obj->quan)
                quan -= obj->quan;
    }
    else
    {

        quan = obj->quan;
    }
    obj->quan = quan;
    obj->unpaid = 0;
    ltmp = bp->price * quan;
    buy = PAY_BUY;

    if (itemize)
    {
        char qbuf[BUFSZ];
        sprintf(qbuf,"%s for %ld %s.  Pay?", quan == 1L ?
                Doname2(obj) : doname(obj), ltmp, currency(ltmp));
        if (yn(qbuf) == 'n')
        {
            buy = PAY_SKIP;
        }
        else if (quan < bp->bquan && !consumed)
        {
            obj->quan = bp->bquan - save_quan;
            verbalize("%s for the other %s before buying %s.",
                      ANGRY(shkp) ? "Pay" : "Please pay", xname(obj),
                      save_quan > 1L ? "these" : "this one");
            buy = PAY_SKIP;
        }
    }
    if (buy == PAY_BUY && u.ugold + ESHK(shkp)->credit < ltmp)
    {
        You("don't%s have gold%s enough to pay for %s.",
            stashed_gold ? " seem to" : "",
            (ESHK(shkp)->credit > 0L) ? " or credit" : "",
            doname(obj));
        buy = itemize ? PAY_SKIP : PAY_CANT;
    }

    if (buy != PAY_BUY)
    {

        obj->quan = save_quan;
        obj->unpaid = 1;
        return buy;
    }

    pay(ltmp, shkp);
    shk_names_obj(shkp, obj, consumed ?
                  "paid for %s at a cost of %ld gold piece%s.%s" :
                  "bought %s for %ld gold piece%s.%s", ltmp, "");
    obj->quan = save_quan;

    if (consumed)
    {
        if (quan != bp->bquan)
        {

            bp->bquan = obj->quan;
            obj->unpaid = 1;
            bp->useup = 0;
            buy = PAY_SOME;
        }
        else
        {
            obj_extract_self(obj);

            dealloc_obj(obj);
            *obj_p = 0;
        }
    }
    else if (itemize)
            update_inventory();
    return buy;
}
