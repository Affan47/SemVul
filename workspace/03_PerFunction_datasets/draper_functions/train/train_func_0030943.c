gb2312_encoder(const ucs4_t *data, Py_ssize_t *length)
{
    DBCHAR coded;
    assert(*length == 1);
    if (*data < 0x10000) {
        TRYMAP_ENC(gbcommon, coded, *data) {
            if (!(coded & 0x8000))
                return coded;
        }
    }
    return MAP_UNMAPPABLE;
}
