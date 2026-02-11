editBasis()
{
  	GtkTreeIter node;
   	DataMolcasTree* data = NULL;
	gint atomNumber;
	gint basisNumber;
	MolcasOneBasis* basis;
	gchar* basisName = g_strdup(gtk_entry_get_text(GTK_ENTRY(EntryBasisName)));
	gchar* author = g_strdup(gtk_entry_get_text(GTK_ENTRY(EntryAuthor)));
	gchar* primitive = g_strdup(gtk_entry_get_text(GTK_ENTRY(EntryPrimitive)));
	gchar* contraction = g_strdup(gtk_entry_get_text(GTK_ENTRY(EntryContraction)));
	gchar* ecpType = g_strdup(gtk_entry_get_text(GTK_ENTRY(EntryEcpType)));
	gboolean* expandeds;

	GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeView));

	if(!gtk_tree_model_get_iter_from_string (model, &node, selectedRow)) return;
	gtk_tree_model_get (model, &node, LIST_DATA, &data, -1);


	if(!data) return;

	atomNumber = data->atomNumber;
	basisNumber = data->basisNumber;

	if(atomNumber<0) return;
	if(basisNumber<0) return;

	delete_all_spaces(basisName);
	if(strlen(basisName)<=0) return;

	basis = molcasBasis.atoms[atomNumber].basis;

	if(basis[basisNumber].basisName) g_free(basis[basisNumber].basisName);
	if(basis[basisNumber].author) g_free(basis[basisNumber].author);
	if(basis[basisNumber].primitive) g_free(basis[basisNumber].primitive);
	if(basis[basisNumber].contraction) g_free(basis[basisNumber].contraction);
	if(basis[basisNumber].ecpType) g_free(basis[basisNumber].ecpType);

	basis[basisNumber].basisName = basisName;

	if(this_is_a_backspace(author))
		basis[basisNumber].author = g_strdup("UNK");
	else
		basis[basisNumber].author =  g_strdup(author);

	if(this_is_a_backspace(primitive))
		basis[basisNumber].primitive = g_strdup("UNK");
	else
		basis[basisNumber].primitive = g_strdup(primitive);

	if(this_is_a_backspace(contraction))
		basis[basisNumber].contraction =  g_strdup("UNK");
	else
		basis[basisNumber].contraction =  g_strdup(contraction);

	if(this_is_a_backspace(ecpType))
		basis[basisNumber].ecpType =  g_strdup("UNK");
	else
		basis[basisNumber].ecpType =  g_strdup(ecpType);

	molcasBasis.atoms[atomNumber].basis = basis;

	expandeds = getExpandInfo();
	freeDataMolcasTree();
	rafreshTreeView();
	setExpandeds(expandeds,selectedRow);
	if(expandeds) g_free(expandeds);
}
