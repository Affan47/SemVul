AddCmd(AsmCmdName cmd, AsmMemory mem, CmdSize size)
{
    commands.push_back(new AsmCmd1(cmd, new AsmMemory(mem), size));
}
