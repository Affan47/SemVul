finalStates(FinalState state)
{
    QList<Stone> list;
    if (!isRunning() || state == FinalStateInvalid) {
        return list;
    }

    QByteArray msg("final_status_list ");
    switch (state) {
        case FinalAlive: msg.append("alive"); break;
        case FinalDead: msg.append("dead"); break;
        case FinalSeki: msg.append("seki"); break;
        case FinalWhiteTerritory: msg.append("white_territory"); break;
        case FinalBlackTerritory: msg.append("black_territory"); break;
        case FinalDame: msg.append("dame"); break;
        case FinalStateInvalid:  break;
    }
    msg.append('\n');
    m_process.write(msg);
    if (waitResponse() && !m_response.isEmpty()) {
        foreach (const QString &entry, m_response.split(' ')) {
            list.append(Stone(entry));
        }
    }
    return list;
}
