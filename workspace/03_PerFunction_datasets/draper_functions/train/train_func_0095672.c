add_tokf(char* pp1,int n,TOKENS tok, int* ntok, char* outbuff, int tj)
{
	char* token_start;

	(*ntok)++;


	token_start = outbuff;


	for (tj=0;tj<n;tj++){
		*(outbuff+tj) = *(pp1+tj);
	}
	outbuff = outbuff + (n);
	*(outbuff++) = '\0';


	strcpy(tok[*ntok],token_start);


}
