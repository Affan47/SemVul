registerFunctions(QScriptEngine* engine)
    {
        QScriptValue value = engine->globalObject();
        value.setProperty(QL1S("isPlainHostName"), engine->newFunction(IsPlainHostName));
        value.setProperty(QL1S("dnsDomainIs"), engine->newFunction(DNSDomainIs));
        value.setProperty(QL1S("localHostOrDomainIs"), engine->newFunction(LocalHostOrDomainIs));
        value.setProperty(QL1S("isResolvable"), engine->newFunction(IsResolvable));
        value.setProperty(QL1S("isInNet"), engine->newFunction(IsInNet));
        value.setProperty(QL1S("dnsResolve"), engine->newFunction(DNSResolve));
        value.setProperty(QL1S("myIpAddress"), engine->newFunction(MyIpAddress));
        value.setProperty(QL1S("dnsDomainLevels"), engine->newFunction(DNSDomainLevels));
        value.setProperty(QL1S("shExpMatch"), engine->newFunction(ShExpMatch));
        value.setProperty(QL1S("weekdayRange"), engine->newFunction(WeekdayRange));
        value.setProperty(QL1S("dateRange"), engine->newFunction(DateRange));
        value.setProperty(QL1S("timeRange"), engine->newFunction(TimeRange));


        value.setProperty(QL1S("isResolvableEx"), engine->newFunction(IsResolvableEx));
        value.setProperty(QL1S("isInNetEx"), engine->newFunction(IsInNetEx));
        value.setProperty(QL1S("dnsResolveEx"), engine->newFunction(DNSResolveEx));
        value.setProperty(QL1S("myIpAddressEx"), engine->newFunction(MyIpAddressEx));
        value.setProperty(QL1S("sortIpAddressList"), engine->newFunction(SortIpAddressList));
        value.setProperty(QL1S("getClientVersion"), engine->newFunction(GetClientVersion));
    }
}
