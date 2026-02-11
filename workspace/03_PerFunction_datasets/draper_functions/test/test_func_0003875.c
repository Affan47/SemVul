removeImageReferenceAttached()
{
  if (currentImageDataset) return removeImageReference(*currentImageDataset);
  else return EC_IllegalCall;
}
