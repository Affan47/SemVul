SetCommandLine(PROC * proc, const char * str, int len)
{


	if ((len == 0) && (proc->commandLength == 0))
		return;


	if ((len == proc->commandLength) &&
		(str[0] == proc->command[0]) &&
		(str[len - 1] == proc->command[len - 1]) &&
		(memcmp(str, proc->command, len) == 0))
	{
		return;
	}


	if (proc->command != proc->commandBuffer)
		free(proc->command);

	proc->command = proc->commandBuffer;


	if (len > BUF_COMMAND_LEN)
		proc->command = AllocMemory(len + 1);


	memcpy(proc->command, str, len);
	proc->command[len] = '\0';
	proc->commandLength = len;
}
