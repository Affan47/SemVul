get_background_position (StThemeNode             *self,
                         const ClutterActorBox   *allocation,
                         ClutterActorBox         *result,
                         ClutterActorBox         *texture_coords)
{
  gdouble painting_area_width, painting_area_height;
  gdouble background_image_width, background_image_height;
  gdouble x1, y1;
  gdouble scale_w, scale_h;


  background_image_width = cogl_texture_get_width (self->background_texture);
  background_image_height = cogl_texture_get_height (self->background_texture);


  painting_area_width = allocation->x2 - allocation->x1;
  painting_area_height = allocation->y2 - allocation->y1;


  get_background_scale (self,
                        painting_area_width, painting_area_height,
                        background_image_width, background_image_height,
                        &scale_w, &scale_h);
  background_image_width *= scale_w;
  background_image_height *= scale_h;


  get_background_coordinates (self,
                              painting_area_width, painting_area_height,
                              background_image_width, background_image_height,
                              &x1, &y1);

  if (self->background_repeat)
    {
      gdouble width = allocation->x2 - allocation->x1 + x1;
      gdouble height = allocation->y2 - allocation->y1 + y1;

      *result = *allocation;


      texture_coords->x1 = x1 / background_image_width;
      texture_coords->y1 = y1 / background_image_height;
      texture_coords->x2 = width / background_image_width;
      texture_coords->y2 = height / background_image_height;
    }
  else
    {
      result->x1 = x1;
      result->y1 = y1;
      result->x2 = x1 + background_image_width;
      result->y2 = y1 + background_image_height;

      texture_coords->x1 = texture_coords->y1 = 0;
      texture_coords->x2 = texture_coords->y2 = 1;
    }
}
