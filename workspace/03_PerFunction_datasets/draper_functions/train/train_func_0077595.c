gncOwnerIsValid (const GncOwner *owner)
{
    if (!owner) return FALSE;
    return (owner->owner.undefined != NULL);
}
