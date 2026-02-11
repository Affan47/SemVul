MoveEndLinePageFile() {
    int L = GetVPort()->TP.Row + GetVPort()->Rows - 1;
    int Len = LineLen();

    if (CP.Col == Len && CP.Row == L)
        return MoveFileEnd();
    else if (CP.Col == Len)
        if (MovePageEnd() == 0)
            return 0;
    return MoveLineEnd();
}
