imProcessRenderOp(imImage* image, imRenderFunc render_func, const char* render_name, float* param, int plus)
{
  int ret = 0;

  int counter = imProcessCounterBegin(render_name);
  imCounterTotal(counter, image->depth*image->height, "Rendering...");

  for (int d = 0; d < image->depth; d++)
  {
    switch(image->data_type)
    {
    case IM_BYTE:
      ret = DoRenderOp((imbyte*)image->data[d], image->width, image->height, d, render_func, param, counter, plus);
      break;
    case IM_SHORT:
      ret = DoRenderOp((short*)image->data[d], image->width, image->height, d, render_func, param, counter, plus);
      break;
    case IM_USHORT:
      ret = DoRenderOp((imushort*)image->data[d], image->width, image->height, d, render_func, param, counter, plus);
      break;
    case IM_INT:
      ret = DoRenderOp((int*)image->data[d], image->width, image->height, d, render_func, param, counter, plus);
      break;
    case IM_FLOAT:
      ret = DoRenderOp((float*)image->data[d], image->width, image->height, d, render_func, param, counter, plus);
      break;
    }

    if (!ret)
      break;
  }

  imProcessCounterEnd(counter);

  return ret;
}
