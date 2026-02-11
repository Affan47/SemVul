Java_magick_MagickImage_setNumberColors
    (JNIEnv *env, jobject self, jint numberColors)
{
    Image *image = NULL;
    QuantizeInfo quantize_info;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env,
                             "No image to set the number of unique colors");
	return;
    }

  GetQuantizeInfo(&quantize_info);
  quantize_info.number_colors=numberColors;
  (void) QuantizeImage(&quantize_info,image);
}
