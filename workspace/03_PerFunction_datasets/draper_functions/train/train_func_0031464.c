Match2(int Len, int Pos, hsState *StateMap, const char *Text, const char *String, hsState State) {
    int L = strlen(String);

    int i;
    for( i = 0; i < Pos; i++ )
        if( Text[i] != ' ' ) return 0;

    if (Pos + L <= Len)
        if (StateMap == NULL || IsState(StateMap + Pos, State, L))
            if (strnicmp(String, Text + Pos, L) == 0)
                return 1;
    return 0;
}
