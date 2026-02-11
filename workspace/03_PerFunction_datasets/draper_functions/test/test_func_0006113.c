_InvRotate(int*a, int*b)
{
    *a -= (*b + 1) >> 1;
    *b += (*a + 1) >> 1;
    CHECK2(long_word_flag, *a, *b);
}
