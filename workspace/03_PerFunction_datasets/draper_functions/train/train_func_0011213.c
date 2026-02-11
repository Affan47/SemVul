createWidgetAnnotations(Catalog *catalog) {
  if (terminal) {
    for (int i = 0; i < numChildren; i++)
      widgets[i]->createWidgetAnnotation(catalog);
  } else {
    for (int i = 0; i < numChildren; i++)
      children[i]->createWidgetAnnotations(catalog);
  }
}
