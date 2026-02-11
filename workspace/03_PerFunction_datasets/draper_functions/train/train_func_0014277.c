Do () {
    Command* cmd = (Command*) _info->GetOwner();

    if (cmd != nil) {
        Busy();

#if 1
	unidraw->ExecuteCmd(cmd->Copy());
#else
        if (cmd->Reversible()) {
            cmd = cmd->Copy();
            cmd->Execute();

            if (cmd->Reversible()) {
                cmd->Log();
            } else {
                delete cmd;
            }

        } else {
            cmd->Execute();

            if (cmd->Reversible()) {
                cmd = cmd->Copy();
                cmd->Log();
            }
        }
#endif

        Done();
    }
}
