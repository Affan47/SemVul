gncOwnerGetCustomer (const GncOwner *owner)
{
    if (!owner) return NULL;
    if (owner->type != GNC_OWNER_CUSTOMER) return NULL;
    return owner->owner.customer;
}
