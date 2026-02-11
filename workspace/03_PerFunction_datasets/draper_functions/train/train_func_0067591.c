v2f_checkrorwplus(int argc, char *argv[])
{
	int i,result=0;
	for (i=0;i<argc;i++)
		if (strcmp(argv[i],"-o")==0) {
			char *s=argv[i+1];
			char *t=s;
			int status=0;
			while (*s) {

				switch(status) {
					case 0:
						if (*s=='r')
							status=1;
						else
							status=2;
						*(t++)=*(s++);
						break;
					case 1:
						if (*s=='o')
							status=3;
						else if (*s=='w')
							status=4;
						else if (*s==',')
							status=0;
						else
							status=2;
						*(t++)=*(s++);
						break;
					case 2:
						if (*s==',')
							status=0;
						*(t++)=*(s++);
						break;
					case 3:
						if (*s==',') {
							result |= FLRO;
							status=0;
						} else
							status = 2;
						*(t++)=*(s++);
						break;
					case 4:
						*t=*s;
						if (*s=='+')
							status=5;
						else if (*s==',') {
							result |= FLRW;
							*t='o';
							status = 0;
						} else
							status = 2;
						t++;s++;
						break;
					case 5:
						if (*s==',') {
							result |= FLRWPLUS;
							status = 0;
							t--;
						} else
							status = 2;
						*(t++)=*(s++);
						break;
				}
			}
			switch (status) {
				case 3: result |= FLRO; break;
				case 4: result |= FLRW; break;
				case 5: result |= FLRWPLUS; t--;break;
			}
			*t=0;
		}
	return result;
}
