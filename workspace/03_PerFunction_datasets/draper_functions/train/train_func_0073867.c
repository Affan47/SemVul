comma_number(char *string, u_long sum)
{
	u_long mod = 0;
	char o_bytes[64];

	strcpy(o_bytes,"");
	while(sum>999)
	{
		mod = sum%1000;
		sum = sum/1000;
		sprintf(string,",%-3.3lu%s",mod,o_bytes);
		strcpy(o_bytes,string);
	}
	sprintf(string,"%lu%s",sum,o_bytes);
	return;
}
