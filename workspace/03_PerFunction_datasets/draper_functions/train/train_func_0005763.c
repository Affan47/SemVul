ChangePass(struct NickInfo *nptr, char *newpass)

{
#ifdef CRYPT_PASSWORDS
	char *encr;
#endif

	if (!nptr || !newpass)
		return 0;

	MyFree(nptr->password);

#ifdef CRYPT_PASSWORDS


	encr = hybcrypt(newpass, NULL);
	assert(encr != 0);

	nptr->password = MyStrdup(encr);

#else


	nptr->password = MyStrdup(newpass);

#endif

	return 1;
}
