add_command (Command *const cmd)
{


	cmd->DropReferences.connect_same_thread (*this, boost::bind (&command_death, this, cmd));
	actions.push_back (cmd);
}
