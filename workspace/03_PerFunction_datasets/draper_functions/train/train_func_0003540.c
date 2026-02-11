ho_pixbuf_new_from_objmap (const ho_objmap * obj_in, const unsigned char min,
  const unsigned char max)
{
  int x, y;
  ho_pixbuf *pix = NULL;
  int index = 0;


  pix = ho_pixbuf_new (3, obj_in->width, obj_in->height, 0);
  if (!pix)
    return NULL;


  for (x = 0; x < obj_in->width; x++)
    for (y = 0; y < obj_in->height; y++)
    {
      index = ho_objmap_get (obj_in, x, y);

      if (index)
      {

        ho_pixbuf_set (pix, x, y, 0, min + (max - min) * (index % 12) / 12);
        ho_pixbuf_set (pix, x, y, 1, min + (max - min) * (index % 6) / 6);
        ho_pixbuf_set (pix, x, y, 2, min + (max - min) * (index % 9) / 9);
      }
      else
      {

        ho_pixbuf_set (pix, x, y, 0, 255);
        ho_pixbuf_set (pix, x, y, 1, 255);
        ho_pixbuf_set (pix, x, y, 2, 255);
      }
    }

  return pix;
}
