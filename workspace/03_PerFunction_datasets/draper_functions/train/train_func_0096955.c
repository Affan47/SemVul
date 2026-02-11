cmp(const FWObject *obj,
                      bool recursive) throw(FWException)
{
    if (!FWObject::cmp(obj, recursive)) return false;

    const DynamicGroup *group = DynamicGroup::constcast(obj);
    return group->m_filter == m_filter;
}
