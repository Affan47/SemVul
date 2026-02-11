HandlePetNameQueryOpcode(WorldPacket& recv_data)
{
    DETAIL_LOG("HandlePetNameQuery. CMSG_PET_NAME_QUERY");

    uint32 petnumber;
    ObjectGuid petguid;

    recv_data >> petnumber;
    recv_data >> petguid;

    SendPetNameQuery(petguid, petnumber);
}
