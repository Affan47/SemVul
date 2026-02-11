gap_mov_render_create_or_replace_tempsel_image(gint32 channel_id
                  , GapMovValues *val_ptr
                  , gboolean all_empty
                  )
{
  if(val_ptr->tmpsel_image_id >= 0)
  {
    gimp_image_delete(val_ptr->tmpsel_image_id);
  }

  val_ptr->tmpsel_image_id = gimp_image_new(gimp_drawable_width(channel_id)
                                           ,gimp_drawable_height(channel_id)
                                           ,GIMP_RGB
                                           );

  gimp_selection_all(val_ptr->tmpsel_image_id);
  val_ptr->tmpsel_channel_id = gimp_selection_save(val_ptr->tmpsel_image_id);

  if(!all_empty)
  {
    gap_layer_copy_content(val_ptr->tmpsel_channel_id
                          ,channel_id
                          );
  }
}
