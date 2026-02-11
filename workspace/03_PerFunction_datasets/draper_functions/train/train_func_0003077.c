p_do_active_layer_tracking(gint32 image_id
                       ,GapVinVideoInfo *vin_ptr
                       ,gchar *ref_layer_name
                       ,gint32 ref_layer_stackpos
                       )
{
  switch(vin_ptr->active_layer_tracking)
  {
    case GAP_ACTIVE_LAYER_TRACKING_BY_NAME:
      p_set_active_layer_by_name(image_id, ref_layer_name, ref_layer_stackpos);
      break;
    case GAP_ACTIVE_LAYER_TRACKING_BY_STACKPOS:
      p_set_active_layer_by_pos(image_id, ref_layer_stackpos);
      break;
    default:
      break;
  }
}
