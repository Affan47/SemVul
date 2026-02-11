SendPetNameInvalid(uint32 error, const std::string& name)
{

    WorldPacket data(SMSG_PET_NAME_INVALID, 4 + name.size() + 1 + 1);
    data << uint32(error);
    data << name;
    data << uint8(0);
    SendPacket(&data);
}
