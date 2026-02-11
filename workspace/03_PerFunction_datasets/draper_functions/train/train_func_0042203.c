setLine()
{
    outDebug(4,std::cout << "setLine:" << mHistoryPtr << " size:" << mHistory.size() << " " << mHistory[mHistoryPtr].toStdString() << std::endl);
    if (mHistoryPtr < -1 || mHistoryPtr >= (signed) mHistory.size())
        return;
    if (mHistoryPtr != -1)
        this->setText(mHistory[mHistoryPtr]);
    else
        this->setText("");
}
