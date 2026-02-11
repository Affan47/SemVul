FindFold(int Line) {
    int f = FindNearFold(Line);
    if (f != -1)
        if (FF[f].line == Line)
            return f;
    return -1;
}
