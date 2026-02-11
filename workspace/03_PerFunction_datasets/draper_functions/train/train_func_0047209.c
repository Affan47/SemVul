aes_arg_convert(PyObject *obj, void *adr)
{
        if (PyCObject_Check(obj) && PyCObject_GetDesc(obj) == aes_descriptor) {
                *((AES_KEY**) adr) = (AES_KEY*) PyCObject_AsVoidPtr(obj);
                return 1;
        } else {
                TYPE_ERR("Expected an AES key as an argument.");
                return 0;
        }
}
