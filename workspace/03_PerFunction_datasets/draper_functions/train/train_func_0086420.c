token_bucket(void)
{
    if(token_bucket_tokens == 0) {
        token_bucket_tokens = MIN(MAX_TOKEN_BUCKET_TOKENS,
                                  100 * (now.tv_sec - token_bucket_time));
        token_bucket_time = now.tv_sec;
    }

    if(token_bucket_tokens == 0)
        return 0;

    token_bucket_tokens--;
    return 1;
}
