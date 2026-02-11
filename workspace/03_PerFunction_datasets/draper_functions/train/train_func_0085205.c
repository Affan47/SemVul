prev_hist()
{
    return H.Pos == 0 ? NULL : H.Lines[--H.Pos];
}
