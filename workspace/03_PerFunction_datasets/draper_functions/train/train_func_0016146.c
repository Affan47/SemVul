main(int argc, char *argv[])
{
    int needleLen, haystackLen;
    char *needle, *haystack, *ptr;
    FILE *input;
    if (argc < 3){
        fprintf(stderr, "Missing paramerter\n");
        abort();
    }
    input = fopen(argv[1], "r");

    while (1){
        if (fscanf(input, "%i %i", &haystackLen, &needleLen) != 2){
            fprintf(stderr, "Missing number of notes\n");
            abort();
        }

        if (needleLen == 0 || haystackLen == 0)
            break;

        CHKMLC(needle = malloc(sizeof(char) * needleLen));
        CHKMLC(haystack = malloc(sizeof(char) * haystackLen));

        music_read(input, haystackLen, haystack);
        music_read(input, needleLen, needle);

        music_pitch_diff(&haystackLen, haystack);
        music_pitch_diff(&needleLen, needle);

        switch(argv[2][0] - '0'){
            case 1: ptr = strstr_bf(haystack, needle);
                    break;
            case 2: ptr = strstr_kmp(haystack, needle);
                    break;
            case 3: ptr = strstr_bmh(haystack, needle);
                    break;
            case 4: ptr = strstr_bitap(haystack, needle);
                    break;
            default: ptr = strstr(haystack, needle);
        }

        if (ptr != NULL)
            printf("S %li\n", ptr - haystack);
        else
            printf("N\n");

        free(needle);
        free(haystack);
    }
    return EXIT_SUCCESS;
}
