pixmap_from_file(const std::string& file, RefPtr<Bitmap>* bitmap) {
  RefPtr<Pixbuf> pixbuf = Pixbuf::create_from_file(file);
  RefPtr<Pixmap> pixmap;
  if (bitmap)
    pixbuf->render_pixmap_and_mask(pixmap, *bitmap, 255);
  else {
    RefPtr<Bitmap> tmp;
    pixbuf->render_pixmap_and_mask(pixmap, tmp, 255);
  }
  return pixmap;
}
