RefreshImageData(ImageStruct * img, XImageStruct * ximg)
{

    char patient_string[256];

    if (img->error_condition == TRUE) {
      XUTL_DisplayString(&G_xStruct,
			 G_big_window, 0,
			 G_display_width / 8, G_display_height / 2,
			 img->error_message);
    } else {
	XPutImage(G_xStruct->display, ximg->image_window, G_gcimage,
		  ximg->x_image, 0, 0, 0, 0, img->ncols, img->nrows);
	strcpy(patient_string, img->patname);
	strcat(patient_string, " | ");
	strcat(patient_string, img->date);
	strcat(patient_string, " | ");
	strcat(patient_string, img->modality);
	strcat(patient_string, " | ");
	strcat(patient_string, img->study);
#ifdef CTN_MULTIBYTE
	XUTL_DisplayMBString(&G_xStruct,
			     G_big_window, 0,
			     img->xpos, img->ypos - TEXT_POSITION,
			     patient_string, img->encoding);
#else
	XUTL_DisplayString(&G_xStruct,
			   G_big_window, 0,
			   img->xpos, img->ypos - TEXT_POSITION,
			   patient_string);

#endif
    }
    XFlush(G_xStruct->display);
    return;
}
