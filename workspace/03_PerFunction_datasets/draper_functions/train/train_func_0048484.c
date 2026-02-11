strrcmp(s1, s2)
    STR s1, s2; {

    pchar ch1, ch2;
    int l1, l2;

    l1 = strlen(s1);
    l2 = strlen(s2);

    for (ch2 = s2; l1 < l2; ch2++, l2--) ;
    for (ch1 = s1; l1 > l2; ch1++, l1--) ;
    return strcmp(ch1, ch2);
}
