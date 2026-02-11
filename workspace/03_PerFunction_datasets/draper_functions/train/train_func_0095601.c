my_strstr(RESULT * result, RESULT * arg1, RESULT * arg2)
{
    char *p;
    double value;

    char *haystack = R2S(arg1);
    char *needle = R2S(arg2);

    p = strstr(haystack, needle);

    if (p == NULL) {
	value = -1;
    } else {
	value = p - haystack;
    }

    SetResult(&result, R_NUMBER, &value);
}
