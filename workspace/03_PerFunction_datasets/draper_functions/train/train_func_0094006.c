SplitImageList(Image *images)
{
  if ((images == (Image *) NULL) || (images->next == (Image *) NULL))
    return((Image *) NULL);
  images=images->next;
  images->previous->next=(Image *) NULL;
  images->previous=(Image *) NULL;
  return(images);
}
