jaw_impl_ref_relation_set (AtkObject *atk_obj)
{
	if (atk_obj->relation_set) {
		g_object_unref(G_OBJECT(atk_obj->relation_set));
	}

	atk_obj->relation_set = atk_relation_set_new();

	JawObject *jaw_obj = JAW_OBJECT(atk_obj);
	jobject ac = jaw_obj->acc_context;
	JNIEnv *jniEnv = jaw_util_get_jni_env();

	jclass classAccessibleContext = (*jniEnv)->FindClass( jniEnv, "javax/accessibility/AccessibleContext" );
	jmethodID jmid = (*jniEnv)->GetMethodID( jniEnv, classAccessibleContext, "getAccessibleRelationSet", "()Ljavax/accessibility/AccessibleRelationSet;" );
	jobject jrel_set = (*jniEnv)->CallObjectMethod( jniEnv, ac, jmid );

	jclass classAccessibleRelationSet = (*jniEnv)->FindClass( jniEnv, "javax/accessibility/AccessibleRelationSet" );
	jmid = (*jniEnv)->GetMethodID(jniEnv, classAccessibleRelationSet, "toArray", "()[Ljavax/accessibility/AccessibleRelation;");
	jobjectArray jrel_arr = (*jniEnv)->CallObjectMethod(jniEnv, jrel_set, jmid);
	jsize jarr_size = (*jniEnv)->GetArrayLength(jniEnv, jrel_arr);

	jsize i;
	for (i = 0; i < jarr_size; i++) {
		jobject jrel = (*jniEnv)->GetObjectArrayElement(jniEnv, jrel_arr, i);
		jclass classAccessibleRelation = (*jniEnv)->FindClass( jniEnv, "javax/accessibility/AccessibleRelation" );
		jmid = (*jniEnv)->GetMethodID( jniEnv, classAccessibleRelation, "getKey", "()Ljava/lang/String;" );
		jstring jrel_key = (*jniEnv)->CallObjectMethod( jniEnv, jrel, jmid );

		AtkRelationType rel_type = get_atk_relation_type_from_java_key(jniEnv, jrel_key);

		jmid = (*jniEnv)->GetMethodID( jniEnv, classAccessibleRelation, "getTarget", "()[Ljava/lang/Object;" );
		jobjectArray jtarget_arr = (*jniEnv)->CallObjectMethod( jniEnv, jrel, jmid );
		jsize jtarget_size = (*jniEnv)->GetArrayLength(jniEnv, jtarget_arr);

		jsize j;
		for (j = 0; j < jtarget_size; j++) {
			jobject jtarget = (*jniEnv)->GetObjectArrayElement(jniEnv, jtarget_arr, j);
			jclass classAccessible = (*jniEnv)->FindClass( jniEnv, "javax/accessibility/Accessible" );
			if ((*jniEnv)->IsInstanceOf(jniEnv, jtarget, classAccessible)) {
				jmid = (*jniEnv)->GetMethodID(jniEnv, classAccessible, "getAccessibleContext", "()Ljavax/accessibility/AccessibleContext;");
				jobject target_ac = (*jniEnv)->CallObjectMethod( jniEnv, jtarget, jmid );

				JawImpl *target_obj = jaw_impl_get_instance( jniEnv, target_ac );
				atk_object_add_relationship(atk_obj, rel_type, target_obj);
			}
		}
	}

	g_object_ref (atk_obj->relation_set);

	return atk_obj->relation_set;
}
