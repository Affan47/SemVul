ajRound(ajuint i, ajuint vround)
{
    ajuint modi;

    modi = i % vround;
    if(!modi)
        return i;

    return i + (vround - modi);
}
