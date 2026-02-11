__dbj_dbt_copyout(
    JNIEnv *jenv, const DBT *dbt, jbyteArray *jarr, jobject jdbt)
{
	jbyteArray newarr = (*jenv)->NewByteArray(jenv, (jsize)dbt->size);
	if (newarr == NULL)
		return;
	(*jenv)->SetByteArrayRegion(jenv, newarr, 0, (jsize)dbt->size,
	    (jbyte *)dbt->data);
	(*jenv)->SetObjectField(jenv, jdbt, dbt_data_fid, newarr);
	(*jenv)->SetIntField(jenv, jdbt, dbt_offset_fid, 0);
	(*jenv)->SetIntField(jenv, jdbt, dbt_size_fid, (jint)dbt->size);
	if (jarr != NULL)
		*jarr = newarr;
	else
		(*jenv)->DeleteLocalRef(jenv, newarr);
}
