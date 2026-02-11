checkbssids(char *bssidlist)
{
	int first = 1;
	int i = 0;
	char *list, *tmp;
	int nbBSSID = 0;

	if(bssidlist == NULL) return -1;

#define IS_X(x) ((x) == 'X' || (x) == 'x')
#define VALID_CHAR(x)   ((IS_X(x)) || hexCharToInt(x) > -1)

#define VALID_SEP(arg)	( ((arg) == '_') || ((arg) == '-') || ((arg) == ':') )
	list = strdup(bssidlist);
	do
	{
		tmp = strsep(&list, ",");

		if (tmp == NULL)
			break;

		++nbBSSID;

		if(strlen(tmp) != 17) return -1;


		if(!VALID_CHAR(tmp[ 0])) return -1;
		if(!VALID_CHAR(tmp[ 1])) return -1;
		if(!VALID_SEP( tmp[ 2])) return -1;


		if(!VALID_CHAR(tmp[ 3])) return -1;
		if(!VALID_CHAR(tmp[ 4])) return -1;
		if(!VALID_SEP( tmp[ 5])) return -1;


		if(!VALID_CHAR(tmp[ 6])) return -1;
		if(!VALID_CHAR(tmp[ 7])) return -1;
		if(!VALID_SEP( tmp[ 8])) return -1;


		if(!VALID_CHAR(tmp[ 9])) return -1;
		if(!VALID_CHAR(tmp[10])) return -1;
		if(!VALID_SEP( tmp[11])) return -1;


		if(!VALID_CHAR(tmp[12])) return -1;
		if(!VALID_CHAR(tmp[13])) return -1;
		if(!VALID_SEP( tmp[14])) return -1;


		if(!VALID_CHAR(tmp[15])) return -1;
		if(!VALID_CHAR(tmp[16])) return -1;


		if(first)
		{
			for(i=0; i< 17; i++)
				if( IS_X(tmp[i])) return -1;

			opt.firstbssid = (unsigned char *) malloc(sizeof(unsigned char));
			getmac(tmp, 1, opt.firstbssid);
			first = 0;
		}

	} while(list);


	return nbBSSID;
}
