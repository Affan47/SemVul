draw(int X, int Y, int W, int H, int cx, int cy) {
  if (image_) image_->draw(X, Y, W, H, cx, cy);
  else Fl_Image::draw(X, Y, W, H, cx, cy);
}
