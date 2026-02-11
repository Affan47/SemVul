reload() {

  int		i;
  FILE		*fp;
  uchar		header[64];
  Fl_Image	*img;

  if (!name_) return;

  if ((fp = fopen(name_, "rb")) != NULL) {
    fread(header, 1, sizeof(header), fp);
    fclose(fp);
  } else {
    return;
  }


  if (memcmp(header, "#define", 7) == 0)
    img = new Fl_XBM_Image(name_);
  else if (memcmp(header, "/* XPM */", 9) == 0)
    img = new Fl_XPM_Image(name_);
  else {

    for (i = 0, img = 0; i < num_handlers_; i ++) {
      img = (handlers_[i])(name_, header, sizeof(header));

      if (img) break;
    }
  }

  if (img) {
    if (alloc_image_) delete image_;

    alloc_image_ = 1;

    if ((img->w() != w() && w()) || (img->h() != h() && h())) {

      Fl_Image *temp = img->copy(w(), h());
      delete img;
      image_ = temp;
    } else {
      image_ = img;
    }

    update();
  }
}
