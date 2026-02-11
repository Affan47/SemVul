start_eating(struct obj *otmp)
{
#ifdef DEBUG
    debugpline("start_eating: %lx (victual = %lx)", otmp, victual.piece);
    debugpline("reqtime = %d", victual.reqtime);
    debugpline("(original reqtime = %d)", objects[otmp->otyp].oc_delay);
    debugpline("nmod = %d", victual.nmod);
    debugpline("oeaten = %d", otmp->oeaten);
#endif
    victual.fullwarn = victual.doreset = false;
    victual.eating = true;

    if (otmp->otyp == CORPSE)
    {
        cprefx(victual.piece->corpsenm);
        if (!victual.piece || !victual.eating)
        {

            return;
        }
    }

    if (bite()) return;

    if (++victual.usedtime >= victual.reqtime)
    {

        done_eating(victual.reqtime > 1 ? true : false);
        return;
    }

    sprintf(msgbuf, "eating %s", food_xname(otmp, true));
    set_occupation(eatfood, msgbuf, 0);
}
