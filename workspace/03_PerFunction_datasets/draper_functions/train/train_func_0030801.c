ExecuteCmd(Command *command) {
    if (command) {
	if (command->Reversible()) {
	    command->Execute();
            if (command->Reversible()) {
                command->Log();
            } else {
                delete command;
            }
	}
	else {
	    command->Execute();
            if (command->Reversible()) {
                command->Log();
            }
	}
    }
}
