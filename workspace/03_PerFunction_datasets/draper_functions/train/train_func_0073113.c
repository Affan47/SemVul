billterm_to_ui (GncBillTerm *term, GtkWidget *desc, BillTermNB *notebook)
{
    gtk_entry_set_text (GTK_ENTRY (desc), gncBillTermGetDescription (term));
    notebook->type = gncBillTermGetType (term);

    switch (notebook->type)
    {
    case GNC_TERM_TYPE_DAYS:
        get_int (notebook->days_due_days, term, gncBillTermGetDueDays);
        get_int (notebook->days_disc_days, term, gncBillTermGetDiscountDays);
        get_numeric (notebook->days_disc, term, gncBillTermGetDiscount);
        break;

    case GNC_TERM_TYPE_PROXIMO:
        get_int (notebook->prox_due_day, term, gncBillTermGetDueDays);
        get_int (notebook->prox_disc_day, term, gncBillTermGetDiscountDays);
        get_numeric (notebook->prox_disc, term, gncBillTermGetDiscount);
        get_int (notebook->prox_cutoff, term, gncBillTermGetCutoff);
        break;
    }
}
