jaw_object_finalize (GObject *gobject)
{

	JawObject *jaw_obj = JAW_OBJECT(gobject);
	AtkObject *atk_obj = ATK_OBJECT(gobject);
	JNIEnv *jniEnv = jaw_util_get_jni_env();

	if (atk_obj->name != NULL) {
		(*jniEnv)->ReleaseStringUTFChars(jniEnv, jaw_obj->jstrName, atk_obj->name);
		(*jniEnv)->DeleteGlobalRef(jniEnv, jaw_obj->jstrName);
		jaw_obj->jstrName = NULL;
		atk_obj->name = NULL;
	}

	if (atk_obj->description != NULL) {
		(*jniEnv)->ReleaseStringUTFChars(jniEnv, jaw_obj->jstrDescription, atk_obj->description);
		(*jniEnv)->DeleteGlobalRef(jniEnv, jaw_obj->jstrDescription);
		jaw_obj->jstrDescription = NULL;
		atk_obj->description = NULL;
	}

	if (jaw_obj->state_set != NULL) {
		g_object_unref(G_OBJECT(jaw_obj->state_set));
	}


	G_OBJECT_CLASS(jaw_object_parent_class)->finalize(gobject);
}
