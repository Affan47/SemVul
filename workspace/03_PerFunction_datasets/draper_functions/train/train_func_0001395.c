se_PauseGameTimer(bool p){
    if (se_mainGameTimer && sn_GetNetState()!=nCLIENT)
        se_mainGameTimer->pause(p);
}
