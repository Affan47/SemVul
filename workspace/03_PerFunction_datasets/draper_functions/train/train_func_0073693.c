mlmatch(char* str, char* exp, char* get)
{
list_t * l = NULL;
list_t * r = NULL;
list_t * a = NULL;
list_t * g = NULL;
list_t * x = NULL;
int len_g,len_r,min_len_g,min_len_r;

l=tokenize_html(str);
r=tokenize_exp(exp);
g=tokenize_exp(get);

#ifdef DEBUG_MLEX
printf("print STRING\n");
print_toklist(l,str,0);
printf("print EXPRESSION\n");
print_toklist(r,exp,0);
printf("print GET\n");
print_toklist(g,get,0);
printf("print FILE\n");
printf("%s",str);
printf("\n");
#endif

len_g = list_len(g);
len_r = list_len(r);
min_len_g = exp_min_len(g);
min_len_r = exp_min_len(r);


if(len_g != len_r)
	{
	DBG("Internal: len(exp)=%d != len(get)=%d",
		len_r,len_g);
	ERROR_PRINT("list_len(g) != list_len(r)\n");
	goto abort;
	}
if(min_len_g != min_len_r)
	{
	DBG("Internal: min_len(exp)=%d != min_len(get)=%d",
		min_len_r,min_len_g);
	ERROR_PRINT("exp_min_len(g) != exp_min_len(r)\n");
	goto abort;
	}


if ( len_g > 2 * min_len_g )
	{
	DBG("Internal: ambiguous match, too many optional tags\n");
	DBG("Internal: concrete tags are %d, while optionals are %d\n",
		min_len_g,len_g);
	}

a = mlmatch_aux(l,r,str,exp,min_len_r);

#ifdef DEBUG_MLEX
printf("print ANSWERS\n");
print_anslist(a,str);
printf("\n");
#endif

x = mlmatch_epurate(a,str,g,get);

list_free(a,free_answer);
abort:
list_free(l,free);
list_free(r,free);
list_free(g,free);

return x;
}
