regret(int token)
{
	if (++regretp >= REGDEP)
		panic(catgets(catd, CATSET, 128, "Too many regrets"));
	regretstack[regretp] = token;
	lexstring[STRINGLEN-1] = '\0';
	string_stack[regretp] = savestr(lexstring);
	numberstack[regretp] = lexnumber;
}
