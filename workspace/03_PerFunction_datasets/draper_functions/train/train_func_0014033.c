hit_return_msg()
{
    int		save_p_more = p_more;

    p_more = FALSE;
    if (msg_didout)
	msg_putchar('\n');
    if (got_int)
	MSG_PUTS(_("Interrupt: "));

    MSG_PUTS_ATTR(_("Press ENTER or type command to continue"), hl_attr(HLF_R));
    if (!msg_use_printf())
	msg_clr_eos();
    p_more = save_p_more;
}
