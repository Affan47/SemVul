printsoa(struct string *soa) {
    char *s;
    int i;

    s = (char *)soa->data;
    i = 0;
    while (i < soa->len) {
	putchar(s[i]);
	if (s[i++] == ' ')
	    break;
    }
    while (i < soa->len) {
	putchar(s[i]);
	if (s[i++] == ' ')
	    break;
    }
    printf("(\n\t\t\t\t");
    while (i < soa->len) {
	putchar(s[i]);
	if (s[i++] == ' ')
	    break;
    }
    printf("; Serialnumber\n\t\t\t\t");
    while (i < soa->len) {
	if (s[i] == ' ')
	    break;
	putchar(s[i++]);
    }
    i++;
    printf("\t; Refresh\n\t\t\t\t");
    while (i < soa->len) {
	if (s[i] == ' ')
	    break;
	putchar(s[i++]);
    }
    i++;
    printf("\t; Retry\n\t\t\t\t");
    while (i < soa->len) {
	if (s[i] == ' ')
	    break;
	putchar(s[i++]);
    }
    i++;
    printf("\t; Expire\n\t\t\t\t");
    while (i < soa->len) {
	putchar(s[i++]);
    }
    printf(" )\t; Minimum TTL\n");
}
