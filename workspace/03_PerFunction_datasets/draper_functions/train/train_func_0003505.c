FastUnicodeCompare ( register uint16_t str1[], register uint16_t length1,
                            register uint16_t str2[], register uint16_t length2)
{
    register uint16_t     c1,c2;
    register uint16_t     temp;
    register uint16_t*    lowerCaseTable;

    lowerCaseTable = gLowerCaseTable;

    while (1) {
        c1 = 0;
        c2 = 0;
        while (length1 && c1 == 0) {
            c1 = *(str1++);
            --length1;
            if ((temp = lowerCaseTable[c1>>8]) != 0)
                c1 = lowerCaseTable[temp + (c1 & 0x00FF)];
        }
        while (length2 && c2 == 0) {
            c2 = *(str2++);
            --length2;
            if ((temp = lowerCaseTable[c2>>8]) != 0)
                c2 = lowerCaseTable[temp + (c2 & 0x00FF)];
        }
        if (c1 == ':') {
		c1 = '/';
        }
        if (c2 == ':') {
		c2 = '/';
        }
        if (c1 != c2)
            break;
        if (c1 == 0)
            return 0;
    }
    if (c1 < c2)
        return -1;
    else
        return 1;
}
