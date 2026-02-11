GdipLoadImageFromFile (GDIPCONST WCHAR *file, GpImage **image)
{
	FILE		*fp = NULL;
	GpImage		*result = NULL;
	GpStatus	status = Ok;
	ImageFormat	format, public_format;
	char		*file_name = NULL;
	char		format_peek[MAX_CODEC_SIG_LENGTH];
	int		format_peek_sz;

	if (!image || !file)
		return InvalidParameter;

	file_name = (char *) ucs2_to_utf8 ((const gunichar2 *)file, -1);
	if (!file_name) {
		*image = NULL;
		return InvalidParameter;
	}

	fp = fopen (file_name, "rb");
	if (!fp) {
		GdipFree (file_name);
		return OutOfMemory;
	}

	format_peek_sz = fread (format_peek, 1, MAX_CODEC_SIG_LENGTH, fp);
	format = get_image_format (format_peek, format_peek_sz, &public_format);
	fseek (fp, 0, SEEK_SET);

	switch (format) {
	case BMP:
		status = gdip_load_bmp_image_from_file (fp, &result);
		break;
	case TIF:
		status = gdip_load_tiff_image_from_file (fp, &result);
		break;
	case GIF:
		status = gdip_load_gif_image_from_file (fp, &result);
		break;
	case PNG:
		status = gdip_load_png_image_from_file (fp, &result);
		break;
	case JPEG:
		status = gdip_load_jpeg_image_from_file (fp, file_name, &result);
		break;
	case ICON:
		status = gdip_load_ico_image_from_file (fp, &result);
		break;
	case WMF:
		status = gdip_load_wmf_image_from_file (fp, &result);
		break;
	case EMF:
		status = gdip_load_emf_image_from_file (fp, &result);
		break;
	case EXIF:
		status = NotImplemented;
		break;
	default:
		status = OutOfMemory;
		break;
	}

	if (result && (status == Ok))
		result->image_format = public_format;

	fclose (fp);
	GdipFree (file_name);

	*image = result;
	if (status != Ok) {
		*image = NULL;
	} else if (result && (result->type == ImageTypeBitmap) && !result->active_bitmap) {

		gdip_bitmap_setactive (result, NULL, 0);
	}

	return status;
}
