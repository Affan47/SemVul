cJSONUtils_InplaceDecodePointerString(char *string)
{
	char *s2=string;
	for (;*string;s2++,string++) *s2=(*string!='~')?(*string):((*(++string)=='0')?'~':'/');
	*s2=0;
}
