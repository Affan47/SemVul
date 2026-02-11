synchronize_sinks (GnlOperation * operation)
{

  GST_DEBUG_OBJECT (operation, "num_sinks:%d , realsinks:%d, dynamicsinks:%d",
      operation->num_sinks, operation->realsinks, operation->dynamicsinks);

  if (operation->num_sinks == operation->realsinks)
    return;

  if (operation->num_sinks > operation->realsinks) {
    while (operation->num_sinks > operation->realsinks)
      if (!(add_sink_pad (operation))) {
        break;
      }
  } else {


    while (operation->num_sinks < operation->realsinks)
      if (!remove_sink_pad (operation, NULL))
        break;
  }
}
