mkMPair(Dt_t * d, mpair * obj, MPairDisc * disc)
{
    mpair *ap;

    if (disc->flist) {
	ap = disc->flist;
	disc->flist = (mpair *) (ap->link.right);
    } else
	ap = GNEW(mpair);
    ap->id = obj->id;
    ap->v = obj->v;
    return ap;
}
