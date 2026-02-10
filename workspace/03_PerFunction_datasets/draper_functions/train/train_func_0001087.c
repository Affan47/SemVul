getByteArrayFieldValue(JNIEnv *env,
                                      jobject obj,
                                      const char *fieldName,
                                      jfieldID *fieldID,
                                      int *size)
{
    jclass objClass = 0;
    jfieldID objFieldID = 0;
    jobject byteArrayObj = 0;
    unsigned char *byteArray = NULL;
    char *byteArrayCpy = NULL;

    if (fieldID == NULL) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return NULL;
	}
	objFieldID =
            (*env)->GetFieldID(env, objClass, fieldName, "[B");
    }
    else if (*fieldID == 0) {
	objClass = (*env)->GetObjectClass(env, obj);
	if (objClass == 0) {
	    return NULL;
	}
	objFieldID = *fieldID =
	    (*env)->GetFieldID(env, objClass, fieldName, "[B");
    }
    else {
	objFieldID = *fieldID;
    }
    if (objFieldID == 0) {
	return NULL;
    }


    byteArrayObj = (*env)->GetObjectField(env, obj, objFieldID);
    if (byteArrayObj == NULL) {
        return NULL;
    }


    *size = (*env)->GetArrayLength(env, byteArrayObj);
    if (*size == 0) {
        return NULL;
    }


    byteArray = (jbyte *) (*env)->GetByteArrayElements(env, byteArrayObj, 0);
    byteArrayCpy = (unsigned char *) AcquireMemory(*size);
    if (byteArray == NULL) {
        return NULL;
    }
    memcpy(byteArrayCpy, byteArray, *size);
    (*env)->ReleaseByteArrayElements(env, byteArrayObj, byteArray, JNI_ABORT);

    return byteArrayCpy;
}
