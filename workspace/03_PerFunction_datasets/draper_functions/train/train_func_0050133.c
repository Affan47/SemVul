fast_unicode_compare ( const hfsp_unistr255 *ustr1,
			      const hfsp_unistr255 *ustr2)
{
    register UInt16     c1,c2;
    register SInt32	diff;
    register UInt16     temp;
    register UInt16	length1 = ustr1->strlen;
    register UInt16	length2 = ustr2->strlen;
    register UInt16*    lowerCaseTable = gLowerCaseTable;
    register UInt16*	str1 = ustr1->name;
    register UInt16*	str2 = ustr2->name;

    while (1) {

        c1 = c2 = 0;

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
	diff = c2-c1;
        if (diff)
            break;
        if (c1 == 0)
            return 0;
    }
    return diff;
}
