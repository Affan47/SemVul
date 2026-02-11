parseRemoteData(const QByteArray& data, const QString& addr)
{
    int result = -1;
    QString input = QString(data);

    if (input.contains(QString("|ap|")))
    {
        addPlayerIP((int)(data[4] - '0'), data, addr);

    }
    else if (input.contains("|dp|"))
    {
        delPlayerIP(addr);

    }
    else if (input.contains("|rp|"))
    {
        result = parsePlayerReply(data, addr);

    }
    else if (input.contains("|rg|"))
    {
        sendGuiData(addr);

    }
    else if (input.contains("|s|"))
    {
        if (!mGameStarted)
        {
            mpGameLogic->startGame(mGameCount);
            mGameStarted = true;
            for(int i = 0; i < mGameCount; i++)
            {
                sendPlayerData(i);
            }

        }
    }
    else if (input.contains("|c|"))
    {
        if (mGameStarted)
        {
            mGameStarted = false;
            mpGameLogic->stopGame();

        }
    }
    else
    {
        printf("Error transmission data : %s\n", data.data());
    }

    return result;
}
