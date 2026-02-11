qtdemux_parse_udta (GstQTDemux * qtdemux, GNode * udta)
{
  GNode *meta;
  GNode *ilst;
  GNode *xmp_;
  GNode *node;
  gint i;

  meta = qtdemux_tree_get_child_by_type (udta, FOURCC_meta);
  if (meta != NULL) {
    ilst = qtdemux_tree_get_child_by_type (meta, FOURCC_ilst);
    if (ilst == NULL) {
      GST_LOG_OBJECT (qtdemux, "no ilst");
      return;
    }
  } else {
    ilst = udta;
    GST_LOG_OBJECT (qtdemux, "no meta so using udta itself");
  }

  GST_DEBUG_OBJECT (qtdemux, "new tag list");
  if (!qtdemux->tag_list) {
    qtdemux->tag_list = gst_tag_list_new_empty ();
    gst_tag_list_set_scope (qtdemux->tag_list, GST_TAG_SCOPE_GLOBAL);
  } else {
    qtdemux->tag_list = gst_tag_list_make_writable (qtdemux->tag_list);
  }

  i = 0;
  while (i < G_N_ELEMENTS (add_funcs)) {
    node = qtdemux_tree_get_child_by_type (ilst, add_funcs[i].fourcc);
    if (node) {
      gint len;

      len = QT_UINT32 (node->data);
      if (len < 12) {
        GST_DEBUG_OBJECT (qtdemux, "too small tag atom %" GST_FOURCC_FORMAT,
            GST_FOURCC_ARGS (add_funcs[i].fourcc));
      } else {
        add_funcs[i].func (qtdemux, add_funcs[i].gst_tag,
            add_funcs[i].gst_tag_bis, node);
      }
      g_node_destroy (node);
    } else {
      i++;
    }
  }


  g_node_children_foreach (ilst, G_TRAVERSE_ALL,
      (GNodeForeachFunc) qtdemux_tag_add_blob, qtdemux);


  xmp_ = qtdemux_tree_get_child_by_type (udta, FOURCC_XMP_);
  if (xmp_ != NULL) {
    GstBuffer *buf;
    GstTagList *taglist;

    buf = _gst_buffer_new_wrapped (((guint8 *) xmp_->data) + 8,
        QT_UINT32 ((guint8 *) xmp_->data) - 8, NULL);
    taglist = gst_tag_list_from_xmp_buffer (buf);
    gst_buffer_unref (buf);

    qtdemux_handle_xmp_taglist (qtdemux, taglist);
  } else {
    GST_DEBUG_OBJECT (qtdemux, "No XMP_ node found");
  }

}
