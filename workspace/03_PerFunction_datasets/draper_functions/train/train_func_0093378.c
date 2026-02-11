make_md5_salt()
{
	static char salt[13];
	int i;
	char *saltptr = salt;


	salt[0] = '$';
	salt[1] = '1';
	salt[2] = '$';


	for (i = 3; i <= 10; i++)
		salt[i] = saltChars[random() % 64];


	salt[11] = '$';
	salt[12] = '\0';

	return saltptr;
}
