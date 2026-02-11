hexToByte(char** ptrptr)
{
	char a = toupper(**ptrptr);
	(*ptrptr)++;
	char b = toupper(**ptrptr);
	(*ptrptr)++;
	if(a>='A') a=a-'A'+10;
	else a-='0';
	if(b>='A') b=b-'A'+10;
	else b-='0';
	return ((unsigned char)a<<4)|(unsigned char)b;
}
