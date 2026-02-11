dropped_container(struct obj *obj, struct monst *shkp, bool sale)
{
    struct obj *otmp;


    for (otmp = obj->cobj; otmp; otmp = otmp->nobj)
    {
        if (otmp->oclass == COIN_CLASS) continue;

        if (!otmp->unpaid && !(sale && saleable(shkp, otmp)))
                otmp->no_charge = 1;

        if (Has_contents(otmp))
                dropped_container(otmp, shkp, sale);
    }
}
