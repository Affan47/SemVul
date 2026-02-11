ExecCommand(ExCommands Command, ExState &State) {
    switch (Command) {
    case ExBlockCopy:
        return BlockCopy(0);
    case ExBlockCopyAppend:
        return BlockCopy(1);
    default:
        ;
    }
    return EList::ExecCommand(Command, State);
}
