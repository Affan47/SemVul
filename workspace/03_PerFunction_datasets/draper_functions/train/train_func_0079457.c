executeCommand()
{
	if (cb_commands->count() > 0) {
		busy_->start();
		Jid to(commands_[cb_commands->currentItem()].jid);
		QString node = commands_[cb_commands->currentItem()].node;
		AHCExecuteTask* t = new AHCExecuteTask(to,AHCommand(node),pa_->client()->rootTask());
		connect(t,SIGNAL(finished()),SLOT(commandExecuted()));
		t->go(true);
	}
}
