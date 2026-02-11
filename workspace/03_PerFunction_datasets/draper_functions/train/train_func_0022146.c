postWidgetsLoad (Catalog *catalog)
{


  for (int i = 0; i < numFields; i++) {
    rootFields[i]->fillChildrenSiblingsID();
    rootFields[i]->createWidgetAnnotations(catalog);
  }
}
