GetOpcodeName(unsigned int id)
{
    uint32 t = sizeof(worldOpcodeNames);
    if(id > MAX_OPCODE_ID)
        return "OPCODE_INVALID";
    if(id >= sizeof(worldOpcodeNames) / sizeof(char*))
        return "OPCODE_NAME_UNKNOWN";
    return worldOpcodeNames[id];
}
