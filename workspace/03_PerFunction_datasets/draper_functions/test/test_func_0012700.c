buildTokenInfo(const char *key, kvp_value *value, gpointer data)
{
    struct token_accounts_info *tokenInfo = (struct token_accounts_info*)data;
    struct account_token_count* this_account;


    tokenInfo->total_count += kvp_value_get_gint64(value);


    this_account = (struct account_token_count*)
                   g_new0(struct account_token_count, 1);


    this_account->account_name = (char*)key;
    this_account->token_count = kvp_value_get_gint64(value);


    tokenInfo->accounts = g_list_prepend(tokenInfo->accounts, this_account);
}
