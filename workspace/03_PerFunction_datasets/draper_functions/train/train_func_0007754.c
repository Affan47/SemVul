range(char *argv[])
{
	char *q;
	int min, max;
	int i;

	while(*argv){
		q = *argv;
		if(strchr(hex, q[0]) == 0){
    err:
			fprint(2, "unicode: bad range %s\n", *argv);
			return "bad range";
		}
		min = strtoul(q, &q, 16);
		if(min<0 || min>Runemax || *q!='-')
			goto err;
		q++;
		if(strchr(hex, *q) == 0)
			goto err;
		max = strtoul(q, &q, 16);
		if(max<0 || max>Runemax || max<min || *q!=0)
			goto err;
		i = 0;
		do{
			Bprint(&bout, "%.4x %C", min, min);
			i++;
			if(min==max || (i&7)==0)
				Bprint(&bout, "\n");
			else
				Bprint(&bout, "\t");
			min++;
		}while(min<=max);
		argv++;
	}
	return 0;
}
