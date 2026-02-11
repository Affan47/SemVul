Java_org_xmlsoft_Node_removePropImpl
(JNIEnv *env, jobject obj, jstring jname) {
    xmlNode *node = findNode(env, obj);
    const xmlChar *name = (xmlChar*)(*env)->GetStringUTFChars(env, jname, NULL);
    jboolean deleted = JNI_FALSE;

    xmlAttr *attr = node->properties;
    while(attr!=NULL) {
        if(xmlStrcmp(attr->name, name)==0) {
            xmlRemoveProp(attr);
            deleted = JNI_TRUE;
        }
        attr = attr->next;
    }
    (*env)->ReleaseStringUTFChars(env, jname, (const char*)name);

    return deleted;
}
