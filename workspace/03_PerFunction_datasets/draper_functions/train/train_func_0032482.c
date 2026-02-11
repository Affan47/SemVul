gnc_budget_clone(const GncBudget* old_b)
{
    GncBudget* new_b;
    Account* root;
    CloneBudgetData_t clone_data;

    g_return_val_if_fail(old_b != NULL, NULL);

    ENTER(" ");

    new_b = gnc_budget_new(qof_instance_get_book(old_b));
    gnc_budget_begin_edit(new_b);
    gnc_budget_set_name(new_b, gnc_budget_get_name(old_b));
    gnc_budget_set_description(new_b, gnc_budget_get_description(old_b));
    gnc_budget_set_recurrence(new_b, gnc_budget_get_recurrence(old_b));
    gnc_budget_set_num_periods(new_b, gnc_budget_get_num_periods(old_b));

    root = gnc_book_get_root_account(qof_instance_get_book(old_b));
    clone_data.old_b = old_b;
    clone_data.new_b = new_b;
    clone_data.num_periods = gnc_budget_get_num_periods(new_b);
    gnc_account_foreach_descendant(root, clone_budget_values_cb, &clone_data);

    gnc_budget_commit_edit(new_b);

    LEAVE(" ");

    return new_b;
}
