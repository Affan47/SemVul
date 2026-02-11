colorspace_convert_lookup_getput (ColorspaceConvert * convert)
{
  int i;

  convert->getline = NULL;
  convert->getline16 = NULL;
  for (i = 0; i < sizeof (lines) / sizeof (lines[0]); i++) {
    if (lines[i].format == convert->from_format) {
      convert->getline = lines[i].getline;
      convert->getline16 = lines[i].getline16;
      break;
    }
  }
  convert->putline = NULL;
  convert->putline16 = NULL;
  for (i = 0; i < sizeof (lines) / sizeof (lines[0]); i++) {
    if (lines[i].format == convert->to_format) {
      convert->putline = lines[i].putline;
      convert->putline16 = lines[i].putline16;
      break;
    }
  }
  GST_DEBUG ("get %p put %p", convert->getline, convert->putline);

  if (convert->getline16 == NULL) {
    convert->getline16 = getline16_convert;
  }
  if (convert->putline16 == NULL) {
    convert->putline16 = putline16_convert;
  }

  if (convert->from_spec == convert->to_spec) {
    convert->matrix = matrix_identity;
    convert->matrix16 = matrix16_identity;
  } else if (convert->from_spec == COLOR_SPEC_RGB
      && convert->to_spec == COLOR_SPEC_YUV_BT470_6) {
    convert->matrix = matrix_rgb_to_yuv_bt470_6;
    convert->matrix16 = matrix16_rgb_to_yuv_bt470_6;
  } else if (convert->from_spec == COLOR_SPEC_RGB
      && convert->to_spec == COLOR_SPEC_YUV_BT709) {
    convert->matrix = matrix_rgb_to_yuv_bt709;
    convert->matrix16 = matrix16_rgb_to_yuv_bt709;
  } else if (convert->from_spec == COLOR_SPEC_YUV_BT470_6
      && convert->to_spec == COLOR_SPEC_RGB) {
    convert->matrix = matrix_yuv_bt470_6_to_rgb;
    convert->matrix16 = matrix16_yuv_bt470_6_to_rgb;
  } else if (convert->from_spec == COLOR_SPEC_YUV_BT709
      && convert->to_spec == COLOR_SPEC_RGB) {
    convert->matrix = matrix_yuv_bt709_to_rgb;
    convert->matrix16 = matrix16_yuv_bt709_to_rgb;
  } else if (convert->from_spec == COLOR_SPEC_YUV_BT709
      && convert->to_spec == COLOR_SPEC_YUV_BT470_6) {
    convert->matrix = matrix_yuv_bt709_to_yuv_bt470_6;
    convert->matrix16 = matrix16_yuv_bt709_to_yuv_bt470_6;
  } else if (convert->from_spec == COLOR_SPEC_YUV_BT470_6
      && convert->to_spec == COLOR_SPEC_YUV_BT709) {
    convert->matrix = matrix_yuv_bt470_6_to_yuv_bt709;
    convert->matrix16 = matrix16_yuv_bt470_6_to_yuv_bt709;
  }
}
