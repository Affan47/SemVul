doDispatch(Cursor & cur, FuncRequest & cmd)
{
	if (cmd.action() == LFUN_INSET_MODIFY) {
		buffer().removeBiblioTempFiles();
		cache.recalculate = true;
	}
	InsetCommand::doDispatch(cur, cmd);
}
