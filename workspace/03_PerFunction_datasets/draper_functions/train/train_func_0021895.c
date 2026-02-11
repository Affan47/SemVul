Java_magick_MagickImage_setIptcProfile
  (JNIEnv *env, jobject self, jobject profileObj)
{
    unsigned char *info;
    int infoSize = 0;

    Image *image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
       throwMagickException(env, "Cannot obtain image handle");
       return;
    }


    if (profileObj == NULL) {
        throwMagickException(env, "ProfileInfo cannot be null");
        return;
    }


    info = getByteArrayFieldValue(env, profileObj, "info", NULL, &infoSize);

#ifdef DIAGNOSTIC
    fprintf(stderr, "setIptcProfile 8BIM infoSize = %d  info = %p\n\n", infoSize, info);
#endif

    if (info==NULL) {

	RemoveImageProfile(image,"8bim");
    } else {
        StringInfo* profile_info;
        profile_info = AcquireStringInfo(infoSize);
        SetStringInfoDatum(profile_info, info);

	SetImageProfile(image,"8bim",profile_info);
        profile_info=DestroyStringInfo(profile_info);
    }
}
