mx_deform_page_turn_deform (MxDeformTexture   *texture,
                            CoglTextureVertex *vertex,
                            gfloat             width,
                            gfloat             height)
{
  gfloat cx, cy, rx, ry, turn_angle;
  guint shade;

  MxDeformPageTurnPrivate *priv = ((MxDeformPageTurn *)texture)->priv;


  cx = (1.f - priv->period) * width;
  cy = (1.f - priv->period) * height;

  rx = ((vertex->x - cx) * cos (-priv->angle)) -
       ((vertex->y - cy) * sin (-priv->angle)) - priv->radius;
  ry = ((vertex->x - cx) * sin (-priv->angle)) +
       ((vertex->y - cy) * cos (-priv->angle));

  turn_angle = 0.f;
  if (rx > -priv->radius * 2)
    {


      turn_angle = (rx / priv->radius * G_PI_2) - G_PI_2;
      shade = (sin (turn_angle) * 96) + 159;


      cogl_color_set_from_4ub (&vertex->color, shade, shade, shade, 0xff);
    }

  if (rx > 0)
    {


      gfloat small_radius = priv->radius -
        MIN (priv->radius, (turn_angle * 10) / G_PI);


      rx = (small_radius * cos (turn_angle)) + priv->radius;
      vertex->x = (rx * cos (priv->angle)) - (ry * sin (priv->angle)) + cx;
      vertex->y = (rx * sin (priv->angle)) + (ry * cos (priv->angle)) + cy;
      vertex->z = (small_radius * sin (turn_angle)) + priv->radius;
    }
}
