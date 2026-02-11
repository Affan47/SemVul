char_word_case_fold(int c)
{
    return (c >= 0 && c < 128 && (ctypes[(unsigned char)c]&2));
}
