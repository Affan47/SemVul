Import (const char* pathname) {
  GraphicComp* comp = nil;
  const char* creator = ReadCreator(pathname);
  DrawCatalog* catalog = (DrawCatalog*)unidraw->GetCatalog();

  if (strcmp(creator, "drawserv") == 0) {
    catalog->SetImport(true);
    if (catalog->DrawCatalog::Retrieve(pathname, (Component*&) comp)) {
      catalog->SetImport(false);
      catalog->Forget(comp);
      return comp;
    }
    catalog->SetImport(false);
    return nil;
  }
  else if (strcmp(creator, "graphdraw") == 0 ||
	   strcmp(creator, "netdraw") == 0 ||
	   strcmp(creator, "graph-idraw") == 0) {
    static GraphCatalog *graphcatalog = new GraphCatalog("GraphCatalog", new GraphCreator());;
    graphcatalog->SetImport(true);
    if (graphcatalog->Retrieve(pathname, (Component*&) comp)) {
      graphcatalog->SetImport(false);
      graphcatalog->Forget(comp);

      if (chooser_->by_pathname()) {
	return new NodeComp((GraphComp*)comp);
      } else
	return comp;
    }
    catalog->SetImport(false);
    return nil;
  } else
    return FrameImportCmd::Import(pathname);
}
