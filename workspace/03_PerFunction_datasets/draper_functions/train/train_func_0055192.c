ApCopyShared(const Appearance *ap, Appearance *into )
{
  if (ap == NULL) return into;
  into = ApCopyShallow( ap, into );
  if (ap->mat) {
    if (into->mat) MtCopy(ap->mat, into->mat);
    else RefIncr((Ref *)(into->mat = ap->mat));
  }
  if (ap->backmat) {
    if (into->backmat) MtCopy(ap->backmat, into->backmat);
    else RefIncr((Ref *)(into->backmat = ap->backmat));
  }
  if (ap->lighting) {
    if (into->lighting) LmCopy(ap->lighting, into->lighting);
    else RefIncr((Ref *)(into->lighting = ap->lighting));
  }
  if (ap->tex) {
    if (into->tex) TxCopy(ap->tex, into->tex);
    else RefIncr((Ref *)(into->tex = ap->tex));
  }
  return into;
}
