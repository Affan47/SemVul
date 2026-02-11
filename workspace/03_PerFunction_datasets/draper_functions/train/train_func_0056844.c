ReadGraph(istream& in, void* addr1, void* addr2, void* addr3, void* addr4) {
    NodeComp* comp = (NodeComp*)addr1;
    char pathname[BUFSIZ];
    if (ParamList::parse_pathname(in, pathname, BUFSIZ, nil) != 0)
	return -1;


    OverlayComp* parent = (OverlayComp*) comp->GetParent();
    while (parent != nil) {
	if (parent->GetPathName() && strcmp(parent->GetPathName(), pathname) == 0) {
	    cerr << "pathname recursion not allowed (" << pathname << ")\n";
	    return -1;
	}
	parent = (OverlayComp*) parent->GetParent();
    }

    GraphComp* graph = nil;
    GraphCatalog* catalog = (GraphCatalog*) unidraw->GetCatalog();
    catalog->SetImport(true);
    if (catalog->GraphCatalog::Retrieve(pathname, (Component*&)graph)) {
        catalog->SetImport(false);
	catalog->Forget(graph);
        *(GraphComp**)addr2 = graph;
	return 0;
    } else {
        catalog->SetImport(false);
	return -1;
    }
}
