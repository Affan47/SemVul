mm_aes128_block_crypt(PyObject *self, PyObject *args, PyObject *kwdict)
{
        static char *kwlist[] = { "key", "block", "encrypt", NULL };
        unsigned char *input;
        long inputlen;
        int encrypt=0;
        PyObject *result;
        AES_KEY *aes_key = NULL;

        if (!PyArg_ParseTupleAndKeywords(args, kwdict,
                                         "O&s#|i:aes128_block_crypt", kwlist,
                                         aes_arg_convert, &aes_key,
                                         &input, &inputlen,
                                         &encrypt))
                return NULL;

        if (inputlen != 16) {
                TYPE_ERR("aes128_block_crypt expected a single block.");
                return NULL;
        }

        if (!(result = PyString_FromStringAndSize(NULL, 16))) {
                PyErr_NoMemory();
                return NULL;
        }
        if (encrypt) {
                AES_encrypt(input, PyString_AS_USTRING(result), aes_key);
        } else {
                AES_decrypt(input, PyString_AS_USTRING(result), aes_key);
        }

        return result;
}
