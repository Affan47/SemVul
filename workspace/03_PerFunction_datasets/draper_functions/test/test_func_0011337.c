reset_dustlen(list_t* pattern)
{
if(pattern != NULL)
	{
	((struct token_t*)pattern->data)->dustlen = 0;
	reset_dustlen(pattern->next);
	}
}
