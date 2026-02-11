default_decompress_parms (j_decompress_ptr cinfo)
{


  switch (cinfo->num_components) {
  case 1:
    cinfo->jpeg_color_space = JCS_GRAYSCALE;
    cinfo->out_color_space = JCS_GRAYSCALE;
    break;

  case 3:
    if (cinfo->saw_JFIF_marker) {
      cinfo->jpeg_color_space = JCS_YCbCr;
    } else if (cinfo->saw_Adobe_marker) {
      switch (cinfo->Adobe_transform) {
      case 0:
	cinfo->jpeg_color_space = JCS_RGB;
	break;
      case 1:
	cinfo->jpeg_color_space = JCS_YCbCr;
	break;
      default:
	WARNMS1(cinfo, JWRN_ADOBE_XFORM, cinfo->Adobe_transform);
	cinfo->jpeg_color_space = JCS_YCbCr;
	break;
      }
    } else {

      int cid0 = cinfo->comp_info[0].component_id;
      int cid1 = cinfo->comp_info[1].component_id;
      int cid2 = cinfo->comp_info[2].component_id;

      if (cid0 == 1 && cid1 == 2 && cid2 == 3)
	cinfo->jpeg_color_space = JCS_YCbCr;
      else if (cid0 == 82 && cid1 == 71 && cid2 == 66)
	cinfo->jpeg_color_space = JCS_RGB;
      else {
	TRACEMS3(cinfo, 1, JTRC_UNKNOWN_IDS, cid0, cid1, cid2);
	cinfo->jpeg_color_space = JCS_YCbCr;
      }
    }

    cinfo->out_color_space = JCS_RGB;
    break;

  case 4:
    if (cinfo->saw_Adobe_marker) {
      switch (cinfo->Adobe_transform) {
      case 0:
	cinfo->jpeg_color_space = JCS_CMYK;
	break;
      case 2:
	cinfo->jpeg_color_space = JCS_YCCK;
	break;
      default:
	WARNMS1(cinfo, JWRN_ADOBE_XFORM, cinfo->Adobe_transform);
	cinfo->jpeg_color_space = JCS_YCCK;
	break;
      }
    } else {

      cinfo->jpeg_color_space = JCS_CMYK;
    }
    cinfo->out_color_space = JCS_CMYK;
    break;

  default:
    cinfo->jpeg_color_space = JCS_UNKNOWN;
    cinfo->out_color_space = JCS_UNKNOWN;
    break;
  }


  cinfo->scale_num = cinfo->block_size;
  cinfo->scale_denom = cinfo->block_size;
  cinfo->output_gamma = 1.0;
  cinfo->buffered_image = FALSE;
  cinfo->raw_data_out = FALSE;
  cinfo->dct_method = JDCT_DEFAULT;
  cinfo->do_fancy_upsampling = TRUE;
  cinfo->do_block_smoothing = TRUE;
  cinfo->quantize_colors = FALSE;

  cinfo->dither_mode = JDITHER_FS;
#ifdef QUANT_2PASS_SUPPORTED
  cinfo->two_pass_quantize = TRUE;
#else
  cinfo->two_pass_quantize = FALSE;
#endif
  cinfo->desired_number_of_colors = 256;
  cinfo->colormap = NULL;

  cinfo->enable_1pass_quant = FALSE;
  cinfo->enable_external_quant = FALSE;
  cinfo->enable_2pass_quant = FALSE;
}
