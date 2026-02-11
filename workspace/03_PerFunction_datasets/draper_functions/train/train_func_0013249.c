rw_preferences_dialog_create_categories_tree_model ()
{
	GtkTreeStore *model;
	GtkTreeIter iter;
	CategoriesTreeItem *category = toplevel;


	model = gtk_tree_store_new (NUM_COLUMNS,
			      G_TYPE_STRING,
			      G_TYPE_INT);


	while (category->category)
    	{
      		CategoriesTreeItem *sub_category = category->children;

		gtk_tree_store_append (model, &iter, NULL);

		gtk_tree_store_set (model, &iter,
			  CATEGORY_COLUMN, gettext (category->category),
			  PAGE_NUM_COLUMN, category->notebook_page,
			  -1);


		while (sub_category->category)
		{
	  		GtkTreeIter child_iter;

	  		gtk_tree_store_append (model, &child_iter, &iter);

			gtk_tree_store_set (model, &child_iter,
				CATEGORY_COLUMN, gettext (sub_category->category),
				PAGE_NUM_COLUMN, sub_category->notebook_page,
			      -1);

	  		sub_category++;
		}

		category++;
	}

	return GTK_TREE_MODEL (model);
}
