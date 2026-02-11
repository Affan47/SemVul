auth_pop(void)
{
    char str[1024];

    char *username;
    unsigned int userlen;
    char *pass;
    unsigned int passlen;

    interaction(SASL_CB_AUTHNAME, NULL, "Authname", &username, &userlen);

    printf("C: USER %s\r\n", username);
    prot_printf(pout,"USER %s\r\n", username);
    prot_flush(pout);

    if (prot_fgets(str, 1024, pin) == NULL) {
	imtest_fatal("prot layer failure");
    }

    printf("S: %s", str);

    if (strncasecmp(str, "+OK", 3)) return IMTEST_FAIL;

    interaction(SASL_CB_PASS, NULL, "Please enter your password",
		&pass, &passlen);

    printf("C: PASS <omitted>\r\n");
    prot_printf(pout,"PASS %s\r\n",pass);
    prot_flush(pout);

    if (prot_fgets(str, 1024, pin) == NULL) {
	imtest_fatal("prot layer failure");
    }

    printf("S: %s", str);

    if (!strncasecmp(str, "+OK", 3)) {
	return IMTEST_OK;
    } else {
	return IMTEST_FAIL;
    }
}
