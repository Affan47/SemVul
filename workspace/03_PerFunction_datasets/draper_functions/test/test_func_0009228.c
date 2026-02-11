mecherror_cmp(struct mecherror m1, struct mecherror m2)
{
    if (m1.code < m2.code)
        return -1;
    if (m1.code > m2.code)
        return 1;
    if (m1.mech.length < m2.mech.length)
        return -1;
    if (m1.mech.length > m2.mech.length)
        return 1;
    if (m1.mech.length == 0)
        return 0;
    return memcmp(m1.mech.elements, m2.mech.elements, m1.mech.length);
}
