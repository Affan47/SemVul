do_compile_conditional (LOOPSET *loop, int j)
{
    if ((loop->cmds[j].ci == IF || loop->cmds[j].ci == ELIF) &&
	loop_cmd_nodol(loop, j) && loop_cmd_nosub(loop, j)) {
	return 1;
    } else {
	return 0;
    }
}
