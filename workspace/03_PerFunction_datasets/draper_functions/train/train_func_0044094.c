jaw_text_get_range_extents (AtkText *text,
		gint start_offset, gint end_offset,
		AtkCoordType coord_type, AtkTextRectangle *rect)
{
	if (rect == NULL) {
		return;
	}

	JawObject *jaw_obj = JAW_OBJECT(text);
	TextData *data = jaw_object_get_interface_data(jaw_obj, INTERFACE_TEXT);
	jobject atk_text = data->atk_text;

	JNIEnv *jniEnv = jaw_util_get_jni_env();
	jclass classAtkText = (*jniEnv)->FindClass(jniEnv, "org/GNOME/Accessibility/AtkText");
	jmethodID jmid = (*jniEnv)->GetMethodID(jniEnv, classAtkText, "get_range_extents", "(III)Ljava/awt/Rectangle;");
	jobject jrect = (*jniEnv)->CallObjectMethod(jniEnv, atk_text, jmid, (jint)start_offset, (jint)end_offset, (jint)coord_type);

	if (!jrect) {
		return;
	}

	jaw_util_get_rect_info(jniEnv, jrect, &(rect->x), &(rect->y), &(rect->width), &(rect->height));
}
