mswings(struct monst *mtmp, struct obj *otemp)
{
    if (!flags.verbose || Blind || !mon_visible(mtmp))
            return;
    pline("%s %s %s %s.", Monnam(mtmp),
          (objects[otemp->otyp].oc_dir & PIERCE) ? "thrusts" : "swings",
          mhis(mtmp), singular(otemp, xname));
}
