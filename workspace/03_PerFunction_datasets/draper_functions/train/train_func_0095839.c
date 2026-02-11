gncBillTermEqual(const GncBillTerm *a, const GncBillTerm *b)
{
    if (a == NULL && b == NULL) return TRUE;
    if (a == NULL || b == NULL) return FALSE;

    g_return_val_if_fail(GNC_IS_BILLTERM(a), FALSE);
    g_return_val_if_fail(GNC_IS_BILLTERM(b), FALSE);

    if (g_strcmp0(a->name, b->name) != 0)
    {
        PWARN("Names differ: %s vs %s", a->name, b->name);
        return FALSE;
    }

    if (g_strcmp0(a->desc, b->desc) != 0)
    {
        PWARN("Descriptions differ: %s vs %s", a->desc, b->desc);
        return FALSE;
    }

    if (a->type != b->type)
    {
        PWARN("Types differ");
        return FALSE;
    }

    if (a->due_days != b->due_days)
    {
        PWARN("Due days differ: %d vs %d", a->due_days, b->due_days);
        return FALSE;
    }

    if (a->disc_days != b->disc_days)
    {
        PWARN("Discount days differ: %d vs %d", a->disc_days, b->disc_days);
        return FALSE;
    }

    if (!gnc_numeric_equal(a->discount, b->discount))
    {
        PWARN("Discounts differ");
        return FALSE;
    }

    if (a->cutoff != b->cutoff)
    {
        PWARN("Cutoffs differ: %d vs %d", a->cutoff, b->cutoff);
        return FALSE;
    }

    if (a->invisible != b->invisible)
    {
        PWARN("Invisible flags differ");
        return FALSE;
    }


    return TRUE;
}
