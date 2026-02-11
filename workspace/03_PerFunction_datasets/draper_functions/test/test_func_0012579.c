imap_proxycopy(MAILSTREAM *stream, char *sequence, char *mailbox, long int flags)
{
    SE_APP_S args;
    long ret;

    args.folder = mailbox;
    args.flags  = flags;

    if(pith_opt_save_size_changed_prompt)
      (*pith_opt_save_size_changed_prompt)(0L, SSCP_INIT);

    ret = imap_seq_exec(stream, sequence, imap_seq_exec_append, &args);

    if(pith_opt_save_size_changed_prompt)
      (*pith_opt_save_size_changed_prompt)(0L, SSCP_END);

    return(ret);
}
