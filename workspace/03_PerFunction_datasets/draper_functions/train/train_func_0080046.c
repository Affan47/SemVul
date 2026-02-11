eat_newline(Program *prog)
{
    while (ip[0] == '\\' && ip[1] == '\n') {
	loadstart++;
	for (ip += 2; is_space(*ip); ip++);
    }
}
