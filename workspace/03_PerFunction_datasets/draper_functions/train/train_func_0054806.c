make_layer (Display *dpy, Window window, int width, int height, int nblobs)
{
  int i;
  struct layer *layer = (struct layer *) calloc(1, sizeof(*layer));
  int blob_min, blob_max;
  XGCValues gcv;
  layer->nblobs = nblobs;

  layer->blobs = (struct blob **) malloc(sizeof(*layer->blobs)*layer->nblobs);

  blob_max = (width < height ? width : height) / 2;
  blob_min = (blob_max * 2) / 3;
  for (i = 0; i < layer->nblobs; i++){
    int j = blob_max - blob_min;
    layer->blobs[i] = make_blob (dpy, width, height,
				 (j ? random() % j : 0) + blob_min);
  }

  layer->pixmap = XCreatePixmap (dpy, window, width, height, 1);
  layer->gc = XCreateGC (dpy, layer->pixmap, 0, &gcv);

# ifdef HAVE_COCOA
  jwxyz_XSetAlphaAllowed (dpy, layer->gc, True);
# endif

  return layer;
}
