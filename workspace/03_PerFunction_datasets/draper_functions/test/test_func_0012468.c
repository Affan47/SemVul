do_prompt (void)


{	scan_space();
	if (!strncmp(next,"off",3))
	{   promptnotebook=0; next+=3;
	}
	else if (!strncmp(next,"on",2))
	{	promptnotebook=1; output("\n"); next+=2;
	}
	else promptnotebook=!promptnotebook;
}
