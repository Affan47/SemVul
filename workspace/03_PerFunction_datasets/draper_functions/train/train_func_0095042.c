do_init(void)
{
    int rc = pcmk_ok;

    the_cib = cib_new();
    rc = the_cib->cmds->signon(the_cib, crm_system_name, cib_command);
    if (rc != pcmk_ok) {
        crm_err("Signon to CIB failed: %s", pcmk_strerror(rc));
        fprintf(stderr, "Signon to CIB failed: %s\n", pcmk_strerror(rc));
    }

    return rc;
}
