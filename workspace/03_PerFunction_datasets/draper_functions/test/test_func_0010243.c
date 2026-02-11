gst_camerabin_rewrite_tags (GstCameraBin * camera)
{
  const GstTagList *app_tag_list = NULL;
  GstTagList *list = NULL;


  app_tag_list = gst_tag_setter_get_tag_list (GST_TAG_SETTER (camera));


  list = gst_camerabin_get_internal_tags (camera);

  if (app_tag_list) {
    gst_tag_list_insert (list, app_tag_list, GST_TAG_MERGE_REPLACE);
  }


  if (camera->active_bin == camera->vidbin) {
    gst_camerabin_rewrite_tags_to_bin (GST_BIN (camera->active_bin), list);
  } else {

    GstEvent *tagevent = gst_event_new_tag (gst_tag_list_copy (list));
    gst_camerabin_send_img_queue_event (camera, tagevent);
  }

  gst_tag_list_free (list);
}
