capstring(firstchar,string,i)
    char firstchar, *string;
    int i;
{
	if (firstchar != 0) putchar(firstchar);
	putchar( (yytext[i] <= 'Z') ? (string[0] - ' ') : string[0]);
	printf("%s",string+1);
}
