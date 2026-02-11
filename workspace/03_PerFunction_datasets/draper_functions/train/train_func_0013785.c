parseInsert(char* s)
{
	pelem firstelem=NULL;
	pelem momelem=NULL;
	unsigned char digit[8];
	unsigned char digitcount=0;
	int pos=0;
	for (pos=0;pos<1024;pos++)
	{
		if (s[pos]=='[')
			continue;
		if (s[pos]==';' || s[pos]==0)
		{
			if (digitcount<=0)
			{
				digit[0]=0;
				digitcount=1;
			}

			pelem newelem=(pelem)malloc(sizeof(telem));
			for (unsigned char a=0;a<8;a++)
				newelem->digit[a]=digit[a];
			newelem->digitcount=digitcount;
			newelem->next=NULL;
			if (momelem==NULL)
				firstelem=newelem;
			else
				momelem->next=newelem;
			momelem=newelem;
			digitcount=0;
			memset(digit,0,8);
			if (s[pos]==0)
				break;
		}
		else
		if (digitcount<8)
		{
			digit[digitcount]=s[pos]-'0';
			digitcount++;
		}
	}
	return firstelem;
}
