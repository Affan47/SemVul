isRevSubset(const char * s1, const char * end_of_s2, int len)
 {
    while ((len > 0) && (*s1 != '\0') && ((*s1 == *end_of_s2) || (*s1 == '.'))) {
        s1++;
        end_of_s2--;
        len--;
    }
    return (*s1 == '\0');
 }
