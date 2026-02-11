u_iter_sub(Leaf *leaf, ScmObj (*ref)(Leaf*, u_long),
                         int *index, int mask)
{
    int i = *index;
    for (i++; i<=mask; i++) {
        if (U_HAS_ENTRY(leaf, i, mask)) {
            *index = i;
            return ref(leaf, i);
        }
    }
    *index = i;
    return SCM_UNBOUND;
}
