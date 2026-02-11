check_initializer_type(Token *assignee_list, Token *equals, Token *expr_list)
{
    Token *t;
    if( expr_list->next_token == (Token*)NULL ) {
	t = expr_list;
    }
    else {


	t = expr_list->next_token = reverse_tokenlist(expr_list->next_token);
    }


    while( t!=NULL ) {
	assignment_stmt_type(assignee_list,t,t);
	t = t->next_token;
    }
}
