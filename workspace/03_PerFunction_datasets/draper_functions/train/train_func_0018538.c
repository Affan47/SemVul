MarkerNext(int marker)
{
    int line = GetControl()->GetCurrentLine() + 1;
    int newLine = GetControl()->MarkerNext(line, 1 << marker);
    if (newLine != -1)
        GotoLine(newLine);
}
