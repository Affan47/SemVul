Java_ncsa_hdf_hdflib_HDFLibrary_1DF24getimage
( JNIEnv *env,
jclass clss,
jstring filename,
jbyteArray image,
jint width,
jint height)
{
    char  *hdf_file;
    intn   rval;
    jbyte *dat;
    jboolean bb;

    hdf_file =(char *) ENVPTR->GetStringUTFChars(ENVPAR filename,0);
    dat = (jbyte *)ENVPTR->GetPrimitiveArrayCritical(ENVPAR image,&bb);

    rval =  DF24getimage((char *)hdf_file, (VOIDP) dat, (int32) width, (int32) height);

    ENVPTR->ReleaseStringUTFChars(ENVPAR filename,hdf_file);
    if (rval == FAIL) {
        ENVPTR->ReleasePrimitiveArrayCritical(ENVPAR image,dat,JNI_ABORT);
        return JNI_FALSE;
    } else {
        ENVPTR->ReleasePrimitiveArrayCritical(ENVPAR image,dat,0);
        return JNI_TRUE;
    }

}
