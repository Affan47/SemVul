gst_queue2_open_temp_location_file (GstQueue2 * queue)
{
  gint fd = -1;
  gchar *name = NULL;

  if (queue->temp_file)
    goto already_opened;

  GST_DEBUG_OBJECT (queue, "opening temp file %s", queue->temp_template);


  if (!queue->temp_location_set) {

    if (queue->temp_template == NULL)
      goto no_directory;


    name = g_strdup (queue->temp_template);
    fd = g_mkstemp (name);
    if (fd == -1)
      goto mkstemp_failed;


    queue->temp_file = fdopen (fd, "wb+");

    if (queue->temp_file == NULL)
      goto open_failed;

    g_free (queue->temp_location);
    queue->temp_location = name;

    GST_QUEUE2_MUTEX_UNLOCK (queue);


    g_object_notify (G_OBJECT (queue), "temp-location");

    GST_QUEUE2_MUTEX_LOCK (queue);
  } else {


    queue->temp_file = g_fopen (queue->temp_location, "wb+");

    if (queue->temp_file == NULL)
      goto open_failed;
  }
  GST_DEBUG_OBJECT (queue, "opened temp file %s", queue->temp_template);

  return TRUE;


already_opened:
  {
    GST_DEBUG_OBJECT (queue, "temp file was already open");
    return TRUE;
  }
no_directory:
  {
    GST_ELEMENT_ERROR (queue, RESOURCE, NOT_FOUND,
        (_("No Temp directory specified.")), (NULL));
    return FALSE;
  }
mkstemp_failed:
  {
    GST_ELEMENT_ERROR (queue, RESOURCE, OPEN_READ,
        (_("Could not create temp file \"%s\"."), queue->temp_template),
        GST_ERROR_SYSTEM);
    g_free (name);
    return FALSE;
  }
open_failed:
  {
    GST_ELEMENT_ERROR (queue, RESOURCE, OPEN_READ,
        (_("Could not open file \"%s\" for reading."), name), GST_ERROR_SYSTEM);
    g_free (name);
    if (fd != -1)
      close (fd);
    return FALSE;
  }
}
