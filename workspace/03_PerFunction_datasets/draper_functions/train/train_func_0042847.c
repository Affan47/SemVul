add_to_string_list(struct string_list **list,char *string)
{
struct	string_list	*new;

    new = malloc(sizeof *new);
    if ( !new ) return(NULL);
    new->next = *list;
    *list = new;
    new->string = malloc(strlen(string)+1);
    if ( new->string ) {
	strcpy(new->string, string);
    }
    return(new);
}
