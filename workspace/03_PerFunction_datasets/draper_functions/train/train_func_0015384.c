locate_protected_var(ScmObj *var)
{
    ScmObj **slot;

    if (l_protected_vars) {
        for (slot = l_protected_vars;
             slot < &l_protected_vars[l_protected_vars_size];
             slot++)
        {
            if (*slot == var)
                return slot;
        }
    }

    return NULL;
}
