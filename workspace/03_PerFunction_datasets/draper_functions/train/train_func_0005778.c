Jam_CallObjectMethodA(JNIEnv *env, jobject obj, jmethodID methodID,
                              jvalue *jargs) {

    Object **ret, *ob = REF_TO_OBJ(obj);
    MethodBlock *mb = lookupVirtualMethod(ob, methodID);

    if(mb == NULL)
        return NULL;

    ret = executeMethodList(ob, ob->class, mb, (u8*)jargs);
    return addJNILref(*ret);
}
