change_state (GstElement *element, GstStateChange transition)
{
    GstStateChangeReturn ret = GST_STATE_CHANGE_SUCCESS;

    switch (transition) {
      case GST_STATE_CHANGE_NULL_TO_READY:
        break;
      case GST_STATE_CHANGE_READY_TO_PAUSED:
        break;
      case GST_STATE_CHANGE_PAUSED_TO_PLAYING:
        break;
      default:
        break;
    }

    ret = GST_ELEMENT_CLASS(parent_class)->change_state(element, transition);
    if (ret == GST_STATE_CHANGE_FAILURE)
        return ret;

    switch (transition) {
      case GST_STATE_CHANGE_PLAYING_TO_PAUSED:
        break;
      case GST_STATE_CHANGE_PAUSED_TO_READY:
        break;
      case GST_STATE_CHANGE_READY_TO_NULL:
        break;
      default:
        break;
    }

    return ret;
}
