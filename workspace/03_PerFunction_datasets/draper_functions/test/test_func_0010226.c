display_confirm_msg()
{

    ++confirm_msg_used;
    if (confirm_msg != NULL)
	msg_puts_attr(confirm_msg, hl_attr(HLF_M));
    --confirm_msg_used;
}
