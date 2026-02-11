SCEndGame(int option)
{
    if (demoplayback || netgame)
    {
        return false;
    }
    MenuActive = false;
    askforquit = true;
    typeofask = 2;
    if (!netgame && !demoplayback)
    {
        paused = true;
    }
    return true;
}
