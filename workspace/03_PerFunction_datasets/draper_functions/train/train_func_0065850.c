isActive(void) const
{
    const bool parent_active = !d_parent ? true : d_parent->isActive();

    return d_active && parent_active;
}
