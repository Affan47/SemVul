createWidgetAnnotations() {
  if (terminal) {
    for (int i = 0; i < numChildren; i++)
      widgets[i]->createWidgetAnnotation();
  } else {
    for (int i = 0; i < numChildren; i++)
      children[i]->createWidgetAnnotations();
  }
}
