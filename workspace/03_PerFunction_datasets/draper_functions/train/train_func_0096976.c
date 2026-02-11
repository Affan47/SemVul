subagent_init_callback_session(void)
{
    if (agentx_callback_sess == NULL) {
        agentx_callback_sess = netsnmp_callback_open(callback_master_num,
                                                     handle_subagent_response,
                                                     NULL, NULL);
        DEBUGMSGTL(("agentx/subagent", "subagent_init sess %p\n",
                    agentx_callback_sess));
    }
}
