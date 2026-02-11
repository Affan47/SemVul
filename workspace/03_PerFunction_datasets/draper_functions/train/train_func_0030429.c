Java_java_awt_BDFontMetrics_destroyFontN(JNIEnv *env, jobject obj, jlong ftFace)
{
#ifdef HAVE_FT2
    FT_Face face = (FT_Face)(intptr_t)ftFace;

    if (!face) {
        return;
    }

    FT_Done_Face(face);
#endif
}
