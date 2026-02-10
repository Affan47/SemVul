gwy_si_unit_clone_real(GObject *source, GObject *copy)
{
    GwySIUnit *si_unit, *clone;

    g_return_if_fail(GWY_IS_SI_UNIT(source));
    g_return_if_fail(GWY_IS_SI_UNIT(copy));

    si_unit = GWY_SI_UNIT(source);
    clone = GWY_SI_UNIT(copy);
    if (gwy_si_unit_equal(si_unit, clone))
        return;

    g_array_set_size(clone->units, 0);
    g_array_append_vals(clone->units,
                        si_unit->units->data, si_unit->units->len);
    clone->power10 = si_unit->power10;
    g_signal_emit(copy, si_unit_signals[VALUE_CHANGED], 0);
}
