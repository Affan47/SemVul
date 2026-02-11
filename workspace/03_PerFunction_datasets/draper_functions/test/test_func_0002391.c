value(dods_int32 *b) const
{
    if (b && _var->type() == dods_int32_c) {
        memcpy(b, _buf, length() * sizeof(dods_int32));
    }
}
