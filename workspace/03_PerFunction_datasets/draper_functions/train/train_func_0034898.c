Get_Packet_Type( char *packet, int len )
{
    uint32_t        MsgId;
    uint32_t        MsgMagic;
    uint32_t        MsgLen;
    uint32_t        MsgProto;
    T_PositionMsg*  PosMsg;
    PT_MsgHdr       MsgHdr;
    CF_Pilot        new_pilot;
    PCF_Pilot       pp;
    double          alt;
    double          px, py, pz;

    pp = &new_pilot;
    MsgHdr    = (PT_MsgHdr)packet;
    MsgMagic  = XDR_decode<uint32_t> (MsgHdr->Magic);
    MsgId     = XDR_decode<uint32_t> (MsgHdr->MsgId);
    MsgLen    = XDR_decode<uint32_t> (MsgHdr->MsgLen);
    MsgProto  = XDR_decode<uint32_t> (MsgHdr->Version);
    if (len < (int)MsgLen) {
        return pkt_InvLen1;
    } else if ( !((MsgMagic == RELAY_MAGIC)||(MsgMagic == MSG_MAGIC)) ) {
        return pkt_InvMag;
    } else if ( !(MsgProto == PROTO_VER) ) {
        return pkt_InvProto;
    }
    if (MsgId == POS_DATA_ID)
    {
        if (MsgLen < sizeof(T_MsgHdr) + sizeof(T_PositionMsg)) {
            return pkt_InvLen2;
        }
        PosMsg = (T_PositionMsg *) (packet + sizeof(T_MsgHdr));
        px = XDR_decode64<double> (PosMsg->position[X]);
        py = XDR_decode64<double> (PosMsg->position[Y]);
        pz = XDR_decode64<double> (PosMsg->position[Z]);
        if ( (px == 0.0) || (py == 0.0) || (pz == 0.0)) {
            return pkt_InvPos;
        }
#ifdef USE_SIMGEAR
        SGVec3d position(px,py,pz);
        SGGeod GeodPoint;
        SGGeodesy::SGCartToGeod ( position, GeodPoint );
        alt = GeodPoint.getElevationFt();
#else
        pp->SenderPosition.Set (px, py, pz);
        sgCartToGeod ( pp->SenderPosition, pp->GeodPoint );
        alt = pp->GeodPoint.GetZ();
#endif
        if (alt <= -9990.0) {
            return pkt_InvHgt;
        }
        strcpy(pp->aircraft,get_Model(PosMsg->Model));
        strcpy(pp->callsign,get_CallSign(MsgHdr->Callsign));
        if (pp->callsign[0] == 0) {
            return pkt_InvStg1;
        } else if (pp->aircraft[0] == 0) {
            return pkt_InvStg2;
        }
        return pkt_Pos;
    } else if (MsgId == CHAT_MSG_ID) {
        return pkt_Chat;
    }
    return pkt_Other;
}
