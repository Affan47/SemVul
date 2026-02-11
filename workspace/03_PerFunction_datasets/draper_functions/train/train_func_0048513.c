String2Buff0(Object *string, char *buff, int len) {
    int offset = STRING_OFFSET(string);
    Object *array = INST_DATA(string, Object*, value_offset);
    unsigned short *str = ARRAY_DATA(array, unsigned short) + offset;
    char *pntr;

    for(pntr = buff; len > 0; len--)
        *pntr++ = *str++;

    *pntr = '\0';
    return buff;
}
