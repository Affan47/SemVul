propagateMessage(plCreatable* pCre)
{
    const pnNetMsg* desc = GET_Cli2Game(kCli2Game_PropagateBuffer);
    msgparm_t* msg = NCAllocMessage(desc);
    msg[0].fUint = pCre->ClassIndex(PlasmaVer::pvMoul);
    hsRAMStream rs(PlasmaVer::pvMoul);
    fResMgr->lock();
    fResMgr->WriteCreatable(&rs, pCre);
    fResMgr->unlock();
    msg[1].fUint = rs.size();
    msg[2].fData = new uint8_t[msg[1].fUint];
    rs.copyTo(msg[2].fData, msg[1].fUint);
    fSock->sendMsg(msg, desc);
    NCFreeMessage(msg, desc);
}
