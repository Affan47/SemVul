intreturn(void)
{
	if (workspace.stackptr==0)
	{
		error("\rStack underflow error\r");
		Running=FALSE;
		return;
	}
	codeptr=acodeptr+workspace.stack[--workspace.stackptr];
}
