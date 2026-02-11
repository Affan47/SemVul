getStatementAt(int position, int& offset)
{
    oldPosM = searchPosM = sqlM.begin();
    while (true)
    {
        SingleStatement s = getNextStatement();
        if (!s.isValid() || lastPosM - sqlM.begin() >= position)
        {
            offset = oldPosM - sqlM.begin();
            return s;
        }
    }
}
