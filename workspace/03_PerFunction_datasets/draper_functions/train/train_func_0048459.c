LoadImage(int i) {
  Array3Df *destination_image = new Array3Df;

  Array3Df *source_image = source_->GetFloatImage(i);
  filter_->RunFilter(*source_image, destination_image);
  source_->Unpin(i);
  return new Image(destination_image);
}
