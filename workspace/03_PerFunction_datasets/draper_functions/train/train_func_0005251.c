PrintRenderingIntents(void)
{
    cmsUInt32Number Codes[200];
    char* Descriptions[200];
    cmsUInt32Number n, i;

    fprintf(stderr, "%ct<n> rendering intent:\n\n", SW);

    n = cmsGetSupportedIntents(200, Codes, Descriptions);

    for (i=0; i < n; i++) {
        fprintf(stderr, "\t%d - %s\n", Codes[i], Descriptions[i]);
    }
    fprintf(stderr, "\n");
}
