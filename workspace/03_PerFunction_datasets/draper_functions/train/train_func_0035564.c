finalState(const Stone &stone)
{
    if (!isRunning() || !stone.isValid()) {
        return FinalStateInvalid;
    }

    m_process.write("final_status " + stone.toLatin1() + '\n');
    if (waitResponse()) {
        if (m_response == "alive") return FinalAlive;
        else if (m_response == "dead") return FinalDead;
        else if (m_response == "seki") return FinalSeki;
        else if (m_response == "white_territory") return FinalWhiteTerritory;
        else if (m_response == "blacK_territory") return FinalBlackTerritory;
        else if (m_response == "dame") return FinalDame;
        else return FinalStateInvalid;
    } else
        return FinalStateInvalid;
}
