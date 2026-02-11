Java_magick_MagickImage_getNumFrames
  (JNIEnv *env, jobject self)
{
    int count = 0;
    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return 0;
    }

    while (image != NULL) {
        count++;
        image = image->next;
    }

    return count;
}
