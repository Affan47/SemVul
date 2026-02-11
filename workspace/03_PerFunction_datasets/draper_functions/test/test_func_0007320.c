save(Buffer &buffer)
{
    int sz = buffer.putInteger(commands.size());
    for (Commands::iterator i = commands.begin(); i != commands.end(); i++) {
        MsgCommand *cmd = *i;
        sz += cmd->write(buffer);
    }
    return sz;
}
