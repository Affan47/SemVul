save_cb(GtkWidget *widget, HybridGroupAddWindow *window)
{
    GtkTreeModel  *model;
    GtkTreeIter    iter;
    HybridAccount *account;
    HybridModule  *proto;
    HybridIMOps   *ops;
    const gchar   *name;

    model = gtk_combo_box_get_model(GTK_COMBO_BOX(window->account_combo));

    if (!gtk_combo_box_get_active_iter(
                GTK_COMBO_BOX(window->account_combo), &iter)) {

        hybrid_debug_error("groupadd", "no account was choosed.");

        return;
    }

    gtk_tree_model_get(model, &iter,
                    GROUPADD_ACCOUNT_COLUMN, &account,
                    -1);

    name = gtk_entry_get_text(GTK_ENTRY(window->name_entry));

    if (!name || *name == '\0') {

        hybrid_debug_error("groupadd", "no group name was specified.");

        return;
    }

    proto = account->proto;
    ops      = proto->info->im_ops;


    if (ops->group_add) {
        ops->group_add(account, name);
    }


    gtk_widget_destroy(window->window);
}
