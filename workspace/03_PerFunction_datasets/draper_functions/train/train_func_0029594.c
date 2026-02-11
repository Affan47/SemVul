tree_clear_all()
{
	gint i;
	GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeViewProjects));
	GtkTreeStore *store = GTK_TREE_STORE (model);

	if(AllFiles == NULL) return;

	gtk_tree_store_clear(store);

	for(i=0;i<Nfiles;i++) tree_data_destroy (AllFiles[i]);

	g_free(AllFiles);
	AllFiles = NULL;
	Nfiles = 0;

	noeud[GABEDIT_TYPENODE_FIREFLY]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"FireFly");
	noeud[GABEDIT_TYPENODE_GAMESS]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"Gamess");
	noeud[GABEDIT_TYPENODE_GAUSSIAN]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"Gaussian");
	noeud[GABEDIT_TYPENODE_MOLCAS]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"Molcas");
	noeud[GABEDIT_TYPENODE_MOLPRO]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"Molpro");
	noeud[GABEDIT_TYPENODE_MOPAC]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"Mopac");
	noeud[GABEDIT_TYPENODE_MPQC]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"MPQC");
	noeud[GABEDIT_TYPENODE_NWCHEM]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"NWChem");
	noeud[GABEDIT_TYPENODE_PSICODE]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"Psicode");
	noeud[GABEDIT_TYPENODE_ORCA]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"ORCA");
	noeud[GABEDIT_TYPENODE_QCHEM]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"Q-Chem");
	noeud[GABEDIT_TYPENODE_GABEDIT]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"Gabedit");
	noeud[GABEDIT_TYPENODE_XYZ]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"XYZ");
	noeud[GABEDIT_TYPENODE_MOL2]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"Mol2");
	noeud[GABEDIT_TYPENODE_PDB]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"PDB");
	noeud[GABEDIT_TYPENODE_TINKER]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"Tinker");
	noeud[GABEDIT_TYPENODE_GZMAT]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"Gauss zmat");
	noeud[GABEDIT_TYPENODE_MZMAT]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"Mopac zmat");
	noeud[GABEDIT_TYPENODE_HIN]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"Hyperchem");
	noeud[GABEDIT_TYPENODE_OTHER]=CreeNoeud(GTK_TREE_VIEW(treeViewProjects),"Others");
}
