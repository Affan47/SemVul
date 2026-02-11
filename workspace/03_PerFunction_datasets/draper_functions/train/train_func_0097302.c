vdtree_add_by_data(ViewDir *vd, FileData *fd, GtkTreeIter *parent)
{
	GtkTreeStore *store;
	GtkTreeIter child;
	NodeData *nd;
	GdkPixbuf *pixbuf;
	NodeData *end;
	GtkTreeIter empty;

	if (!fd) return;

	if (access_file(fd->path, R_OK | X_OK))
		{
		pixbuf = vd->pf->close;
		}
	else
		{
		pixbuf = vd->pf->deny;
		}

	nd = g_new0(NodeData, 1);
	nd->fd = fd;
	nd->version = fd->version;
	nd->expanded = FALSE;
	nd->last_update = time(NULL);

	store = GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(vd->view)));
	gtk_tree_store_append(store, &child, parent);
	gtk_tree_store_set(store, &child, DIR_COLUMN_POINTER, nd,
					 DIR_COLUMN_ICON, pixbuf,
					 DIR_COLUMN_NAME, nd->fd->name,
					 DIR_COLUMN_COLOR, FALSE, -1);


	end = g_new0(NodeData, 1);
	end->fd = NULL;
	end->expanded = TRUE;

	gtk_tree_store_append(store, &empty, &child);
	gtk_tree_store_set(store, &empty, DIR_COLUMN_POINTER, end,
					  DIR_COLUMN_NAME, "empty", -1);

	if (parent)
		{
		NodeData *pnd;
		GtkTreePath *tpath;

		gtk_tree_model_get(GTK_TREE_MODEL(store), parent, DIR_COLUMN_POINTER, &pnd, -1);
		tpath = gtk_tree_model_get_path(GTK_TREE_MODEL(store), parent);
		if (options->tree_descend_subdirs &&
		    gtk_tree_view_row_expanded(GTK_TREE_VIEW(vd->view), tpath) &&
		    !nd->expanded)
			{
			vdtree_populate_path_by_iter(vd, &child, FALSE, vd->dir_fd);
			}
		gtk_tree_path_free(tpath);
		}
}
