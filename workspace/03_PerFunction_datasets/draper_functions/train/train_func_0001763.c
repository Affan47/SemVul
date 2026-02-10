SCQuitGame(int option)
{
    MenuActive = false;
    askforquit = true;
    typeofask = 1;
    if (!netgame && !demoplayback)
    {
        paused = true;
    }
    return true;
}
