autocomplete_add_token_to_list(const char *token)
{
    struct autocomplete_list *new = malloc(sizeof(struct autocomplete_list));

    strlcpy(new->autocomplete_token, token, sizeof(new->autocomplete_token));
    new->next = NULL;
    autocomplete_backlog++;

    if (autocomplete_tail != NULL)
	autocomplete_tail->next = new;
    if (autocomplete_head == NULL)
	autocomplete_head = new;
    autocomplete_tail = new;
}
