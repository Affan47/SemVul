remove_worn_item(struct obj *obj,
                 bool unchain_ball)
{
    if (donning(obj))
            cancel_don();
    if (!obj->owornmask)
            return;

    if (obj->owornmask & W_ARMOR)
    {
        if (obj == uskin)
        {
            impossible("Removing embedded scales?");
            skinback(true);
        }
        if (obj == uarm) Armor_off();
        else if (obj == uarmc) Cloak_off();
        else if (obj == uarmf) Boots_off();
        else if (obj == uarmg) Gloves_off();
        else if (obj == uarmh) Helmet_off();
        else if (obj == uarms) Shield_off();
        else if (obj == uarmu) Shirt_off();

        else setworn((struct obj *)0, obj->owornmask & W_ARMOR);
    }
    else if (obj->owornmask & W_AMUL)
    {
        Amulet_off();
    }
    else if (obj->owornmask & W_RING)
    {
        Ring_gone(obj);
    }
    else if (obj->owornmask & W_TOOL)
    {
        Blindf_off(obj);
    }
    else if (obj->owornmask & (W_WEP|W_SWAPWEP|W_QUIVER))
    {
        if (obj == uwep)
                uwepgone();
        if (obj == uswapwep)
                uswapwepgone();
        if (obj == uquiver)
                uqwepgone();
    }

    if (obj->owornmask & (W_BALL|W_CHAIN))
    {
        if (unchain_ball) unpunish();
    }
    else if (obj->owornmask)
    {

        setnotworn(obj);
    }
}
