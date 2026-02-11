is_delimeter(char *delimiters, char c) {
		 int i=0,len_delimiters=strlen(delimiters);
		 bool is=false;
		 for (i=0;i<len_delimiters;i++)
			 if (c == delimiters[i]) is=true;
		 return is;
	}
