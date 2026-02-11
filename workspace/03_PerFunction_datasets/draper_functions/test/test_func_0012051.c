gre_print(const u_char *bp, u_int length)
{
	u_int len = length, vers;

	if (len < 2) {
		printf("[|gre]");
		return;
	}
	vers = EXTRACT_16BITS(bp) & GRE_VERS_MASK;
        printf("GREv%u",vers);

        switch(vers) {
        case 0:
            gre_print_0(bp, len);
            break;
        case 1:
            gre_print_1(bp, len);
            break;
	default:
            printf(" ERROR: unknown-version");
            break;
        }
	return;

}
