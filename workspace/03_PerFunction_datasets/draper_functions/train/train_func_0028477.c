childProcessExited(s32 pid)
{
	for (u32 i = 0; i < NR_SHELLS; i++) {
		if (mShellList[i] && mShellList[i]->childProcessExited(pid)) break;
	}
}
