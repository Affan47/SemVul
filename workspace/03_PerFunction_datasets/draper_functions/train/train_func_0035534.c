parse_comment(struct commit_node *cn, char *lbuf, FILE *f)
{
        char cbuf[MAX_COMMENT_SIZE];
        char *cp, *lp;

        memset(cbuf, '\0', sizeof(cbuf));
        cp = cbuf;
        while (begins_with(fgets(lbuf, MAX_LBUF_SIZE, f), COMMENT_TOKEN))
        {
                lp = lbuf + strlen(COMMENT_TOKEN);
                if (cp - cbuf + strlen(lp) < MAX_COMMENT_SIZE) {
                        memcpy(cp, lp, strlen(lp));
                        cp += strlen(lp);
                }
        }
        cn->comment = new_str_after_token(cbuf, "");
        remove_newlines_and_tabs(cn->comment);

        return 0;
}
