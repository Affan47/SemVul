cmd_kill()
{
	if (cmdbuf[0] == '\0')
	{

		return (CC_QUIT);
	}
	cmd_offset = 0;
	cmd_home();
	*cp = '\0';
	updown_match = -1;
	cmd_repaint(cp);


	if (curr_cmdflags & CF_QUIT_ON_ERASE)
		return (CC_QUIT);
	return (CC_OK);
}
