gegl_buffer_iterator_add (GeglBufferIterator  *iterator,
                          GeglBuffer          *buffer,
                          const GeglRectangle *roi,
                          gint                 level,
                          const Babl          *format,
                          guint                flags,
                          GeglAbyssPolicy      abyss_policy)
{
  GeglBufferIterators *i = (gpointer)iterator;
  gint self = 0;
  if (i->iterators+1 > GEGL_BUFFER_MAX_ITERATORS)
    {
      g_error ("too many iterators (%i)", i->iterators+1);
    }

  if (i->iterators == 0)
    {
      memset (i, 0, sizeof (GeglBufferIterators));
    }


  self = i->iterators++;

  if (!roi)
    roi = self==0?&(buffer->extent):&(i->rect[0]);
  i->rect[self]=*roi;

  i->buffer[self]= g_object_ref (buffer);

  if (format)
    i->format[self]=format;
  else
    i->format[self]=buffer->soft_format;
  i->flags[self]=flags;

  if (self==0)
    {
      i->flags[self] |= GEGL_BUFFER_SCAN_COMPATIBLE;
      gegl_buffer_tile_iterator_init (&i->i[self], i->buffer[self], i->rect[self], ((i->flags[self] & GEGL_BUFFER_WRITE) != 0), i->format[self], iterator->level);
    }
  else
    {

      i->rect[self].width = i->rect[0].width;
      i->rect[self].height = i->rect[0].height;

      if (gegl_buffer_scan_compatible (i->buffer[0], i->rect[0].x, i->rect[0].y,
                                       i->buffer[self], i->rect[self].x, i->rect[self].y))
        {
          i->flags[self] |= GEGL_BUFFER_SCAN_COMPATIBLE;
          gegl_buffer_tile_iterator_init (&i->i[self], i->buffer[self], i->rect[self], ((i->flags[self] & GEGL_BUFFER_WRITE) != 0), i->format[self], iterator->level);
        }
    }

  i->buf[self] = NULL;

  if (i->format[self] == i->buffer[self]->soft_format)
    {
      i->flags[self] |= GEGL_BUFFER_FORMAT_COMPATIBLE;
    }
  return self;
}
