gst_mse_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  GstMSE *fs = GST_MSE (object);

  switch (prop_id) {
    case LUMA_PSNR:
      g_value_set_double (value,
          mse_to_db (fs->luma_mse_sum / fs->n_frames, FALSE));
      break;
    case CHROMA_PSNR:
      g_value_set_double (value,
          mse_to_db (fs->chroma_mse_sum / fs->n_frames, TRUE));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
