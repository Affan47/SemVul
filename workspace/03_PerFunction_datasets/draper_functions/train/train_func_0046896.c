jaw_text_get_character_extents (AtkText *text,
		gint offset, gint *x, gint *y,
		gint *width, gint *height,
		AtkCoordType coords)
{
	JawObject *jaw_obj = JAW_OBJECT(text);
	TextData *data = jaw_object_get_interface_data(jaw_obj, INTERFACE_TEXT);
	jobject atk_text = data->atk_text;

	JNIEnv *jniEnv = jaw_util_get_jni_env();
	jclass classAtkText = (*jniEnv)->FindClass(jniEnv, "org/GNOME/Accessibility/AtkText");
	jmethodID jmid = (*jniEnv)->GetMethodID(jniEnv, classAtkText, "get_character_extents", "(II)Ljava/awt/Rectangle;");
	jobject jrect = (*jniEnv)->CallObjectMethod(jniEnv, atk_text, jmid, (jint)offset, (jint)coords);

	if (jrect == NULL) {
		return;
	}

	jaw_util_get_rect_info(jniEnv, jrect, x, y, width, height);
}
