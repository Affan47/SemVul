createWidgetAnnotation() {
  if (widget)
    return;

  Object obj1;
  obj1.initRef(ref.num, ref.gen);
  widget = new AnnotWidget(doc, obj.getDict(), &obj1, field);
  obj1.free();
}
