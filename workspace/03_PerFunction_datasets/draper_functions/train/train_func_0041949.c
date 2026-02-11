gncOwnerEqual (const GncOwner *a, const GncOwner *b)
{
    if (!a || !b) return FALSE;
    if (gncOwnerGetType (a) != gncOwnerGetType (b)) return FALSE;
    return (a->owner.undefined == b->owner.undefined);
}
