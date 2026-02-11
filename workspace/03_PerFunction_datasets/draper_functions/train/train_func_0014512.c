CardPowerOff (reader* globalData, char socket) {
    char cmd[4], ack;
    int retVal, actual, retryTimes = 2;

#ifdef ASE_DEBUG
    syslog(LOG_INFO, "\n CardPowerOff - Enter\n");
#endif

    if ((retVal = cardCommandInit(globalData, socket, 1)))
        return retVal;

    cmd[0] = ASE_PACKET_TYPE(0x50, globalData->commandCounter, socket);
    globalData->commandCounter++;
    globalData->commandCounter %= 4;
    cmd[1] = 0x21;
    cmd[2] = 0x0;
    cmd[3] = cmd[0] ^ cmd[1] ^ cmd[2];

    do {
        lock_mutex(globalData);
        retVal = sendControlCommand(globalData, socket, cmd, 4, &ack, &actual, 0);
        unlock_mutex(globalData);

        retryTimes--;
    } while (retVal != ASE_OK && retryTimes);


    if (retVal < 0) {
        return retVal;
    }

    if (ack != 0x20) {
        return parseStatus(ack);
    }


    if (globalData->cards[(int)socket].status)
	    globalData->cards[(int)socket].status = 1;

#ifdef ASE_DEBUG
    syslog(LOG_INFO, " CardPowerOff - Exit\n");
#endif

    return ASE_OK;
}
