makeInterface(PyObject *self, PyObject *args)
{
    char *name, *extName;
    int name_len, extName_len;

    if (!PyArg_ParseTuple(args, "s#s#",
                          &name, &name_len, &extName, &extName_len))
        return NULL;

    JNIEnv *vm_env = env->get_vm_env();
    jclass _ucl = (jclass) vm_env->FindClass("java/net/URLClassLoader");
    jmethodID mid = vm_env->GetStaticMethodID(_ucl, "getSystemClassLoader",
                                              "()Ljava/lang/ClassLoader;");
    jobject classLoader = vm_env->CallStaticObjectMethod(_ucl, mid);
    const int bytes_len = sizeof(interface_bytes);
    const int len = bytes_len + name_len + extName_len;
    char *buf = (char *) malloc(len);

    if (buf == NULL)
        return PyErr_NoMemory();

    int name_pos = 22;
    int extName_pos = 44;
    jclass cls;

    memcpy(buf, interface_bytes, name_pos);
    memcpy(buf + name_pos + name_len, interface_bytes + name_pos,
           extName_pos - name_pos);
    memcpy(buf + extName_pos + name_len + extName_len,
           interface_bytes + extName_pos, bytes_len - extName_pos);
    extName_pos += name_len;

    *((unsigned short *) (buf + name_pos - 2)) = htons(name_len);
    memcpy(buf + name_pos, name, name_len);

    *((unsigned short *) (buf + extName_pos - 2)) = htons(extName_len);
    memcpy(buf + extName_pos, extName, extName_len);

    cls = vm_env->DefineClass(name, classLoader, (const jbyte *) buf, len);
    free(buf);

    if (cls)
        return t_Class::wrap_Object(Class(cls));

    return PyErr_SetJavaError();
}
