setActive(FbShell *shell)
{
	if (mActiveShell == shell) return false;

	if (mActiveShell) {
		mActiveShell->switchVt(false, shell);
	}

	FbShell *oldActiveShell = mActiveShell;
	mActiveShell = shell;

	if (mActiveShell) {
		mActiveShell->switchVt(true, oldActiveShell);
	}

	return true;
}
