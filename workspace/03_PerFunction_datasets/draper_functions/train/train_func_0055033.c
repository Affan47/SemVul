setWarning() {
  switch (_op._fit) {
  case ResizeOp::FIT_EXACTLY:
    gtk_label_set_text(GTK_LABEL(_warning), _("Note: may change aspect ratio."));
    break;
  case ResizeOp::PAD_TO_FIT:
    gtk_label_set_text(GTK_LABEL(_warning), _("Pads with Gimp background colour"));
    break;
  case ResizeOp::FIT_INSIDE:
    gtk_label_set_text(GTK_LABEL(_warning), "");
    break;
  case ResizeOp::FIT_OUTSIDE:
    gtk_label_set_text(GTK_LABEL(_warning), "");
    break;
  }
}
