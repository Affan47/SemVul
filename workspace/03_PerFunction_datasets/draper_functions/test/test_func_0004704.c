TimeInSeconds(string time)


{
    int hmColonLoc = time.find(":");
    int msColonLoc = time.substr(hmColonLoc+1).find(":");


    if(msColonLoc == -1)
        return TimeInSecondsMMSSXXX(time);
    else
        return 3600*atoi(time.substr(0,hmColonLoc).c_str())
              +TimeInSecondsMMSSXXX(time.substr(hmColonLoc+1));
}
