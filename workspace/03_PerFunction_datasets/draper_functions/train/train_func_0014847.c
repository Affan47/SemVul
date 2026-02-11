process (GeglOperation       *operation,
         GeglBuffer          *input,
         const GeglRectangle *result,
         gint                 level)
{
  GeglChantO   *o = GEGL_CHANT_PROPERTIES (operation);
  GeglBuffer   *source;
  SDL_Surface **sdl_outwin = NULL;

  init_sdl ();
  if (!handle)
    handle = g_timeout_add (500, idle, NULL);

  if (!o->screen ||
       o->width  != result->width ||
       o->height != result->height)
    {
      if (sdl_outwin)
        {
          if (o->screen)
            {
              SDL_FreeSurface (o->screen);
              o->screen = NULL;
            }

          o->screen = SDL_CreateRGBSurface (SDL_SWSURFACE,
                                            result->width, result->height, 32, 0xff0000,
                                            0x00ff00, 0x0000ff, 0x000000);

          *sdl_outwin = o->screen;
          if (!o->screen)
            {
              fprintf (stderr, "CreateRGBSurface failed: %s\n",
                       SDL_GetError ());
              return -1;
            }
        }
      else
        {
          o->screen = SDL_SetVideoMode (result->width, result->height, 32, SDL_SWSURFACE);
          if (!o->screen)
            {
              fprintf (stderr, "Unable to set SDL mode: %s\n",
                       SDL_GetError ());
              return -1;
            }
        }
      o->width  = result->width ;
      o->height = result->height;
    }


  source = gegl_buffer_create_sub_buffer (input, result);
  gegl_buffer_get (source,
       NULL,
       1.0,
       babl_format_new (babl_model ("RGBA"),
                        babl_type ("u8"),
                        babl_component ("B"),
                        babl_component ("G"),
                        babl_component ("R"),
                        babl_component ("A"),
                        NULL),
       ((SDL_Surface*)o->screen)->pixels, GEGL_AUTO_ROWSTRIDE,
       GEGL_ABYSS_NONE);
  g_object_unref (source);

  if (!sdl_outwin)
    {
      SDL_UpdateRect (o->screen, 0, 0, 0, 0);
      SDL_WM_SetCaption (o->window_title, o->icon_title);
    }

  o->width = result->width ;
  o->height = result->height;

  return  TRUE;
}
