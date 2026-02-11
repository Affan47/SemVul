is_token(string& istring,const int i)
{
	return (in_str_array(tokens,istring[i]) && !escaped(istring,i));
}
