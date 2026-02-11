updateLayout(int type, const QList<int> & dataList)
{
    switch(type)
    {
        case KBlocksLayout_Update_FreezePiece:
            updateFreezePiece(dataList);
            break;
        case KBlocksLayout_Update_RemoveLine:
            updateRemoveLine(dataList);
            break;
        case KBlocksLayout_Update_PunishLine:
            updatePunishLine(dataList);
            break;
    }
}
