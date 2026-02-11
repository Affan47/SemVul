setmnotwielded(struct monst *mon, struct obj *obj)
{
    if (obj)
    {
        if (artifact_light(obj) && obj->lamplit)
        {
            end_burn(obj, false);
            if (canseemon(mon))
            {
                pline("%s in %s %s %s glowing.", The(xname(obj)),
                      s_suffix(mon_nam(mon)), mbodypart(mon,HAND),
                      otense(obj, "stop"));
            }
        }
        obj->owornmask &= ~W_WEP;
    }
}
