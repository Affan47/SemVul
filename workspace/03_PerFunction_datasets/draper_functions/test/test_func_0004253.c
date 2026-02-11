addFeuille(GtkTreeIter *parent, MolcasOneBasis* molcasOneBasis, gint atomNumber, gint basisNumber)
{
	GtkTreeIter feuille;
	gchar* texts[lengthList];
	DataMolcasTree* dataTree;
	gint i;
	GtkTreeModel *model;
        GtkTreeStore *store;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeView));
        store = GTK_TREE_STORE (model);

	texts[0] = g_strdup(" ");
	texts[1] = g_strdup(molcasOneBasis->basisName);
	if(strstr(molcasOneBasis->author,"UNK")) texts[2] = g_strdup(" ");
	else texts[2] = g_strdup(molcasOneBasis->author);

	if(strstr(molcasOneBasis->primitive,"UNK")) texts[3] = g_strdup(" ");
	else texts[3] = g_strdup(molcasOneBasis->primitive);

	if(strstr(molcasOneBasis->contraction,"UNK")) texts[4] = g_strdup(" ");
	else texts[4] = g_strdup(molcasOneBasis->contraction);

	if(strstr(molcasOneBasis->ecpType,"UNK")) texts[5] = g_strdup(" ");
	else texts[5] = g_strdup(molcasOneBasis->ecpType);

	dataTree = newDataMolcasTree(atomNumber,basisNumber);

	gtk_tree_store_append(store, &feuille, parent);
       	gtk_tree_store_set (store, &feuille, LIST_ATOM_SYMBOL, texts[0], -1);
       	gtk_tree_store_set (store, &feuille, LIST_BASIS_NAME, texts[1], -1);
       	gtk_tree_store_set (store, &feuille, LIST_AUTHOR, texts[2], -1);
       	gtk_tree_store_set (store, &feuille, LIST_PRIMITIVE, texts[3], -1);
       	gtk_tree_store_set (store, &feuille, LIST_CONTRACTION, texts[4], -1);
       	gtk_tree_store_set (store, &feuille, LIST_ECPTYPE, texts[5], -1);

       	gtk_tree_store_set (store, &feuille, LIST_DATA, dataTree, -1);

	for(i=0;i<lengthList;i++) g_free(texts[i]);
}
