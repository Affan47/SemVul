hashcode (const cl_string& str)
{
    var unsigned long code = 0x61284AF3;


    var long len = str.size();
    var const char * ptr = str.asciz();
    for (; len > 0; len--) {
        var unsigned char c = *ptr++;
        code = (code << 5) | (code >> 27);
        code += (long)c << 16;
        code ^= (long)c;
        code &= 0xFFFFFFFF;
    }
    return code;
}

}
