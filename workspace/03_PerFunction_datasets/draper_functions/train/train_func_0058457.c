mptcp_print(const u_char *cp, u_int len, u_char flags)
{
        struct mptcp_option *opt;
        u_int subtype;

        if (len < 3)
                return 0;

        opt = (struct mptcp_option *) cp;
        subtype = min(MPTCP_OPT_SUBTYPE(opt->sub_etc), MPTCP_SUB_FCLOSE + 1);

        printf(" %s", mptcp_options[subtype].name);
        return mptcp_options[subtype].print(cp, len, flags);
}
