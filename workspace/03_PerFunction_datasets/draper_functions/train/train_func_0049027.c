pattern_fill(char *s, int length, int seed)
{
    int i=0;

    while (i<length) {
        s[i] = ((i+seed) % 96) + 33;
        ++i;
    }
}
