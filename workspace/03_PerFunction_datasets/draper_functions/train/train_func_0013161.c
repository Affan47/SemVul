complexMatch(Address *obj1, Address *obj2,
                            bool recognize_broadcasts,
                            bool recognize_multicasts)
{
    if (obj1==NULL || obj2==NULL) return false;
    ObjectMatcher om;
    om.setRecognizeBroadcasts(recognize_broadcasts);
    om.setRecognizeMulticasts(recognize_multicasts);
    om.setIPV6(ipv6);
    return om.complexMatch(obj1, obj2);
}
