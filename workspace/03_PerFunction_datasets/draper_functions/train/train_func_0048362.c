autoquiver(void)
{
    struct obj *otmp, *oammo = 0, *omissile = 0, *omisc = 0, *altammo = 0;

    if (uquiver)
            return;


    for (otmp = invent; otmp; otmp = otmp->nobj) {
        if (otmp->owornmask || otmp->oartifact || !otmp->dknown) {
            ;
        } else if (otmp->otyp == ROCK ||

                   (objects[otmp->otyp].oc_name_known &&
                    otmp->otyp == FLINT) ||
                   (objects[otmp->otyp].oc_name_known &&
                    otmp->oclass == GEM_CLASS &&
                    objects[otmp->otyp].oc_material == GLASS)) {
            if (uslinging())
                    oammo = otmp;
            else if (ammo_and_launcher(otmp, uswapwep))
                    altammo = otmp;
            else if (!omisc)
                    omisc = otmp;
        } else if (otmp->oclass == GEM_CLASS) {
            ;

        } else if (is_ammo(otmp)) {
            if (ammo_and_launcher(otmp, uwep))

                    oammo = otmp;
            else if (ammo_and_launcher(otmp, uswapwep))
                    altammo = otmp;
            else

                    omisc = otmp;
        } else if (is_missile(otmp)) {

            omissile = otmp;
        } else if (otmp->oclass == WEAPON_CLASS && throwing_weapon(otmp)) {

            if (objects[otmp->otyp].oc_skill == P_DAGGER
                && !omissile)
                    omissile = otmp;
            else
                    omisc = otmp;
        }
    }


    if (oammo)
            setuqwep(oammo);
    else if (omissile)
            setuqwep(omissile);
    else if (altammo)
            setuqwep(altammo);
    else if (omisc)
            setuqwep(omisc);

    return;
}
