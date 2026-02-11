netsnmp_access_defaultrouter_entry_update(netsnmp_defaultrouter_entry *lhs,
                                      netsnmp_defaultrouter_entry *rhs)
{
    int changed = 0;

    if (lhs->dr_addresstype != rhs->dr_addresstype) {
        ++changed;
        lhs->dr_addresstype = rhs->dr_addresstype;
    }

    if (lhs->dr_address_len != rhs->dr_address_len) {
        changed += 2;
        lhs->dr_address_len = rhs->dr_address_len;
        memcpy(lhs->dr_address, rhs->dr_address, rhs->dr_address_len);
    }
    else if (memcmp(lhs->dr_address, rhs->dr_address, rhs->dr_address_len) != 0) {
        ++changed;
        memcpy(lhs->dr_address, rhs->dr_address, rhs->dr_address_len);
    }

    if (lhs->dr_if_index != rhs->dr_if_index) {
        ++changed;
        lhs->dr_if_index = rhs->dr_if_index;
    }

    if (lhs->dr_lifetime != rhs->dr_lifetime) {
        ++changed;
        lhs->dr_lifetime = rhs->dr_lifetime;
    }

    if (lhs->dr_preference != rhs->dr_preference) {
        ++changed;
        lhs->dr_preference = rhs->dr_preference;
    }

    return changed;
}
