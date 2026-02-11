doprompt(krb5_context context, krb5_prompter_fct prompter, void *prompter_data,
         const char *banner, const char *prompttxt, char *out, size_t len)
{
    krb5_prompt prompt;
    krb5_data prompt_reply;
    krb5_error_code retval;

    if (prompttxt == NULL || out == NULL)
        return EINVAL;

    memset(out, 0, len);

    prompt_reply = make_data(out, len);
    prompt.reply = &prompt_reply;
    prompt.prompt = (char *)prompttxt;
    prompt.hidden = 1;

    retval = (*prompter)(context, prompter_data, NULL, banner, 1, &prompt);
    if (retval != 0)
        return retval;

    return 0;
}
