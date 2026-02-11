Java_magick_MagickImage_getColormap__I
  (JNIEnv *env, jobject self, jint index)
{
    Image *image;
    jobject jPixelPacket = NULL;
    jclass pixelPacketClass;
    jmethodID consMethodID;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
        throwMagickException(env, "Unable to obtain image handle");
        return NULL;
    }

    if (index >= image->colors) {
        throwMagickException(env, "Index out of range");
        return NULL;
    }

    pixelPacketClass = (*env)->FindClass(env, "magick/PixelPacket");
    if (pixelPacketClass == 0) {
	throwMagickException(env,
			     "Unable to locate class magick.PixelPacket");
	return NULL;
    }

    consMethodID = (*env)->GetMethodID(env, pixelPacketClass,
				       "<init>", "(IIII)V");
    if (consMethodID == 0) {
	throwMagickException(env, "Unable to construct magick.PixelPacket");
	return NULL;
    }

    jPixelPacket = (*env)->NewObject(env, pixelPacketClass, consMethodID,
		                     (jint) image->colormap[index].red,
		                     (jint) image->colormap[index].green,
		                     (jint) image->colormap[index].blue,
		                     (jint) image->colormap[index].opacity);
    if (jPixelPacket == NULL) {
	throwMagickException(env, "Unable to construct magick.PixelPacket");
	return NULL;
    }

    return jPixelPacket;
}
