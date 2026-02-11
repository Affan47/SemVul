isEmpty () const
{
  return d->resource.isEmpty() && d->contentMimeTypes.isEmpty() && !d->statistics && !d->unsubscribed && d->ancestorDepth == None;
}
