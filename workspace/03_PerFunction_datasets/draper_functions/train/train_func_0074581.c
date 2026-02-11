canvas_init (AmitkCanvas *canvas)
{
  gint i;

  gtk_box_set_homogeneous(GTK_BOX(canvas), FALSE);


  for (i=0;i<4;i++) canvas->arrows[i]=NULL;
  for (i=0;i<8;i++) canvas->target[i]=NULL;
  for (i=0;i<4;i++) canvas->orientation_label[i]=NULL;
  canvas->line_profile_item = NULL;
  canvas->type = AMITK_CANVAS_TYPE_NORMAL;

  canvas->volume = amitk_volume_new();
  amitk_volume_set_corner(canvas->volume, one_point);

  canvas->center = zero_point;

  canvas->active_object = NULL;

  canvas->canvas = NULL;
  canvas->slice_cache = NULL;
  canvas->max_slice_cache_size = 15;
  canvas->slices=NULL;
  canvas->image=NULL;
  canvas->pixbuf=NULL;

  canvas->time_on_image=FALSE;
  canvas->time_label=NULL;

  canvas->pixbuf_width = 128;
  canvas->pixbuf_height = 128;

  canvas->study = NULL;
  canvas->undrawn_rois = NULL;
  canvas->object_items=NULL;

  canvas->next_update = 0;
  canvas->idle_handler_id = 0;
  canvas->next_update_objects = NULL;

}
