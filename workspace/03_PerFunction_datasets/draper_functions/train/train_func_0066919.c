Java_magick_MagickImage_opaqueImage
    (JNIEnv *env, jobject self, jobject target, jobject penColor)
{
    PixelPacket ppTarget, ppPenColor;

    Image *image =
	(Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot obtain image handle");
	return JNI_FALSE;
    }

    if (!getPixelPacket(env, target, &ppTarget) ||
	!getPixelPacket(env, penColor, &ppPenColor)) {
	throwMagickException(env, "Unable to obtain PixelPacket values");
	return JNI_FALSE;
    }

    return OpaqueImage(image, ppTarget, ppPenColor);
}
