gst_template_match_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstTemplateMatch *filter = GST_TEMPLATE_MATCH (object);

  switch (prop_id) {
    case PROP_METHOD:
      switch (g_value_get_int (value)) {
        case 0:
          filter->method = CV_TM_SQDIFF;
          break;
        case 1:
          filter->method = CV_TM_SQDIFF_NORMED;
          break;
        case 2:
          filter->method = CV_TM_CCORR;
          break;
        case 3:
          filter->method = CV_TM_CCORR_NORMED;
          break;
        case 4:
          filter->method = CV_TM_CCOEFF;
          break;
        case 5:
          filter->method = CV_TM_CCOEFF_NORMED;
          break;
      }
      break;
    case PROP_TEMPLATE:
      filter->template = (char *) g_value_get_string (value);
      gst_template_match_load_template (filter);
      break;
    case PROP_DISPLAY:
      filter->display = g_value_get_boolean (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
