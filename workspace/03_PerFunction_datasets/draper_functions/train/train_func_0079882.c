Java_magick_MagickImage_getGenericProfile
  (JNIEnv *env, jobject self, jint index)
{
    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return NULL;
    }

    if (image->generic_profiles >= index) {
        return NULL;
    }

    return getProfileInfo(env, &image->generic_profile[index]);
}
