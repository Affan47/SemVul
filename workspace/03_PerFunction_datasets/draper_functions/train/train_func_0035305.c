snuff_candle(struct obj *otmp)
{
    bool candle = Is_candle(otmp);

    if ((candle || otmp->otyp == CANDELABRUM_OF_INVOCATION) && otmp->lamplit)
    {
        char buf[BUFSZ];
        xchar x, y;
        bool many = candle ? otmp->quan > 1L : otmp->spe > 1;

        get_obj_location(otmp, &x, &y, 0);
        if (otmp->where == OBJ_MINVENT ? cansee(x,y) : !Blind)
        {
            pline("%s %scandle%s flame%s extinguished.",
                  Shk_Your(buf, otmp),
                  (candle ? "" : "candelabrum's "),
                  (many ? "s'" : "'s"), (many ? "s are" : " is"));
        }
        end_burn(otmp, true);
        return true;
    }
    return false;
}
