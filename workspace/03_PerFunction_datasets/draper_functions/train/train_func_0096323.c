WaitSync()
{

    if (GetGraphManager()->SuspendRefNum(GetClientControl(), fSynchroTable, 0x7FFFFFFF) < 0) {
        jack_error("SuspendRefNum error");
        return false;
    } else {
        return true;
    }
}
