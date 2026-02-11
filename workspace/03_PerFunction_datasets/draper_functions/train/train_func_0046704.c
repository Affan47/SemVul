getPktSource(void)
{
    if(EchoMask & srcUSERVALID) {
        if (cci){
            if(call.compare(icall) == 0)
                return 'R';
            else
                return 'r';
        }

        if (ax25Source.compare(call) == 0)
            return 'C';
        else
            return 'S';

    }

    if (EchoMask & srcIGATE){
        if (cci)
            return 'r';
        else
            return 'S';

    }

    if (EchoMask & srcTNC)
        return 'R' ;

    if (EchoMask & srcUSER)
        return 'X';

    if (EchoMask & srcUDP)
        return 'U';

    if (EchoMask & srcBEACON)
        return 'I';

    if (EchoMask & srcSYSTEM)
        return 'Z';

    return 'Z';
}
