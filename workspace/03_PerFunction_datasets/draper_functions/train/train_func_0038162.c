imProcessRenderCosine(imImage* image, float xperiod, float yperiod)
{
  float param[6];
  param[0] = (float)imColorMax(image->data_type);

  if (xperiod == 0.0f) param[1] = 0.0;
  else param[1] = 2.0f * 3.1416f / xperiod;

  if (yperiod == 0.0f) param[2] = 0.0;
  else param[2] = 2.0f * 3.1416f / yperiod;

  param[3] = image->width/2.0f;
  param[4] = image->height/2.0f;

  if (image->data_type < IM_FLOAT)
    param[0] = param[0] / 2.0f;

  if (image->data_type == IM_BYTE)
    param[5] = 1.0f;
  else
    param[5] = 0.0f;

  return imProcessRenderOp(image, do_cosine, "Cosine", param, 0);
}
