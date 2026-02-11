Interpret (Command* cmd) {
    if (cmd->IsA(GROUP_CMD) || cmd->IsA(FRONT_CMD) || cmd->IsA(BACK_CMD)) {
        cmd->GetClipboard()->Append(this);
    } else
	OverlaysComp::Interpret(cmd);
}
