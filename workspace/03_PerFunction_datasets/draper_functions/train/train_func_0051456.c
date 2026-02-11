QCC_PR_LexInteger (void)
{
	int		c;
	int		len;

	len = 0;
	c = *pr_file_p;
	if (pr_file_p[0] == '0' && pr_file_p[1] == 'x')
	{
		pr_token[0] = '0';
		pr_token[1] = 'x';
		len = 2;
		c = *(pr_file_p+=2);
	}
	do
	{
		pr_token[len] = c;
		len++;
		pr_file_p++;
		c = *pr_file_p;
	} while ((c >= '0' && c<= '9') || c == '.' || (c>='a' && c <= 'f'));
	pr_token[len] = 0;
	return atoi (pr_token);
}
