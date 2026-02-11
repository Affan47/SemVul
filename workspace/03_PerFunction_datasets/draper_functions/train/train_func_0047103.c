isMyIp(struct in_addr dst){
    if(string((char *)inet_ntoa(dst)) == "10.10.0.2")
        return true;
    for(map<string, routerInfo>::iterator it = macLookUp.begin(); it != macLookUp.end(); ++it){
        if( (*it).second.self_ip == string((char *)inet_ntoa(dst)) )
            return true;
    }
    return false ;
}
