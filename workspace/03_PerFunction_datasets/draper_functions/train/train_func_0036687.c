webx_pipeline_crop (WebxPipeline *pipeline,
                  gint        width,
                  gint        height,
                  gint        offsx,
                  gint        offsy,
                  gboolean    clip_offsets)
{
  g_return_val_if_fail (WEBX_IS_PIPELINE (pipeline), FALSE);


  if (offsx < 0)
    {
      width += offsx;
      offsx = 0;
    }
  else if (offsx >= pipeline->resize_width)
    {
      offsx = pipeline->resize_width - 1;
    }

  if (offsy < 0)
    {
      height += offsy;
      offsy = 0;
    }
  else if (offsy >= pipeline->resize_height)
    {
      offsy = pipeline->resize_height - 1;
    }

  width = CLAMP (width, 1, pipeline->resize_width);
  height = CLAMP (height, 1, pipeline->resize_height);


  if (clip_offsets)
    {
      if (offsx + width > pipeline->resize_width)
        offsx = pipeline->resize_width - width;
      if (offsy + height > pipeline->resize_height)
        offsy = pipeline->resize_height - height;
    }
  else
    {
      if (offsx + width > pipeline->resize_width)
        width = pipeline->resize_width - offsx;
      if (offsy + height > pipeline->resize_height)
        height = pipeline->resize_height - offsy;
    }

  if (width == pipeline->crop_width
      && height == pipeline->crop_height
      && offsx == pipeline->crop_offsx
      && offsy == pipeline->crop_offsy)
    return FALSE;

  pipeline->crop_width = width;
  pipeline->crop_height = height;
  pipeline->crop_offsx = offsx;
  pipeline->crop_offsy = offsy;
  pipeline->crop_scale_x = 1.0;
  pipeline->crop_scale_y = 1.0;
  webx_pipeline_invalidate (pipeline, TRUE);
  return TRUE;
}
