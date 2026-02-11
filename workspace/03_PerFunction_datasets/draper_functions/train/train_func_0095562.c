Java_magick_MagickImage_scaleImage
    (JNIEnv *env, jobject self, jint cols, jint rows)
{
    Image *image = NULL;
    Image *scaledImage = NULL;
    jobject returnedImage;
    jfieldID magickImageHandleFid = NULL;
    ExceptionInfo exception;

    image = (Image*) getHandle(env, self, "magickImageHandle",
			       &magickImageHandleFid);
    if (image == NULL) {
	throwMagickException(env, "No image to scale");
	return NULL;
    }

    GetExceptionInfo(&exception);
    scaledImage = ScaleImage(image,
			     (unsigned int) cols,
			     (unsigned int) rows,
			     &exception);
    if (scaledImage == NULL) {
	throwMagickApiException(env, "Unable to scale image", &exception);
	DestroyExceptionInfo(&exception);
	return NULL;
    }
    DestroyExceptionInfo(&exception);

    returnedImage = newImageObject(env, scaledImage);
    if (returnedImage == NULL) {
	DestroyImages(scaledImage);
	throwMagickException(env, "Unable to construct magick.MagickImage");
	return NULL;
    }
    setHandle(env, returnedImage, "magickImageHandle",
	      (void*) scaledImage, &magickImageHandleFid);

    return returnedImage;
}
