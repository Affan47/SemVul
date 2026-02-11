Gif_DeleteExtension(Gif_Extension *gfex)
{
  if (!gfex)
    return;
  if (gfex->data && gfex->free_data)
    (*gfex->free_data)(gfex->data);
  Gif_DeleteArray(gfex->application);
  if (gfex->stream) {
    Gif_Stream *gfs = gfex->stream;
    Gif_Extension *prev, *trav;
    for (prev = 0, trav = gfs->extensions;
	 trav && trav != gfex;
	 prev = trav, trav = trav->next)
      ;
    if (trav) {
      if (prev) prev->next = trav->next;
      else gfs->extensions = trav->next;
    }
  }
  Gif_Delete(gfex);
}
