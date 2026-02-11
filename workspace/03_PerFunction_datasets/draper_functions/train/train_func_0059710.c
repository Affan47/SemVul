constant_MODE_S(double *value, char *name, int len)
{
    if (!strnEQ(name + 6, "ET_", 3))
        return EINVAL;

    switch (len >= 9 ? name[9] : -1) {
#ifndef NETSNMP_NO_WRITE_SUPPORT
    case 'A':
        TEST_CONSTANT(value, name, MODE_SET_ACTION);
        break;
    case 'B':
        TEST_CONSTANT(value, name, MODE_SET_BEGIN);
        break;
    case 'C':
        TEST_CONSTANT(value, name, MODE_SET_COMMIT);
        break;
    case 'F':
        TEST_CONSTANT(value, name, MODE_SET_FREE);
        break;
    case 'U':
        TEST_CONSTANT(value, name, MODE_SET_UNDO);
        break;
#endif
    case 'R':
        return constant_MODE_SET_R(value, name, len);
    }
    return EINVAL;
}
