gnc_budget_new(QofBook *book)
{
    GncBudget* budget;

    g_return_val_if_fail(book, NULL);

    ENTER(" ");
    budget = g_object_new(GNC_TYPE_BUDGET, NULL);
    qof_instance_init_data (&budget->inst, GNC_ID_BUDGET, book);

    qof_event_gen( &budget->inst, QOF_EVENT_CREATE , NULL);

    LEAVE(" ");
    return budget;
}
