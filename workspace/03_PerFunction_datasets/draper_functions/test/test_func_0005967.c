I_SetSigTitle(struct SigSet *S, const char *title)
{
    if (title == NULL)
	title = "";
    if (S->title)
	free(S->title);
    S->title = G_store(title);

    return 0;
}
