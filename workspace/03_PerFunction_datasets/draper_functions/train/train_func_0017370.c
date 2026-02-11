gst_ximagesink_ximage_destroy (GstXImageSink * ximagesink,
    GstXImageBuffer * ximage)
{
  g_return_if_fail (ximage != NULL);
  g_return_if_fail (GST_IS_XIMAGESINK (ximagesink));


  GST_OBJECT_LOCK (ximagesink);


  if (ximagesink->cur_image == ximage) {
    ximagesink->cur_image = NULL;
  }


  if (!ximagesink->xcontext) {
    GST_DEBUG_OBJECT (ximagesink, "Destroying XImage after XContext");
#ifdef HAVE_XSHM
    if (ximage->SHMInfo.shmaddr != ((void *) -1)) {
      shmdt (ximage->SHMInfo.shmaddr);
    }
#endif
    goto beach;
  }

  g_mutex_lock (ximagesink->x_lock);

#ifdef HAVE_XSHM
  if (ximagesink->xcontext->use_xshm) {
    if (ximage->SHMInfo.shmaddr != ((void *) -1)) {
      XShmDetach (ximagesink->xcontext->disp, &ximage->SHMInfo);
      XSync (ximagesink->xcontext->disp, 0);
      shmdt (ximage->SHMInfo.shmaddr);
    }
    if (ximage->ximage)
      XDestroyImage (ximage->ximage);

  } else
#endif
  {
    if (ximage->ximage) {
      XDestroyImage (ximage->ximage);
    }
  }

  XSync (ximagesink->xcontext->disp, FALSE);

  g_mutex_unlock (ximagesink->x_lock);

beach:
  GST_OBJECT_UNLOCK (ximagesink);

  if (ximage->ximagesink) {

    ximage->ximagesink = NULL;
    gst_object_unref (ximagesink);
  }

  return;
}
