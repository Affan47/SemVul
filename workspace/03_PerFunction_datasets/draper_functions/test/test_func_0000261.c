Java_magick_MagickImage_getColorProfile
  (JNIEnv *env, jobject self)
{
    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return NULL;
    }
    return getProfileInfo(env, &image->color_profile);
}
