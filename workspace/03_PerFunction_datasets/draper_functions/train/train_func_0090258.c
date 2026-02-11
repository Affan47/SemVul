StartIfaceDeclaration(string ifaceName)
{
    if (!IfaceDefined(ifaceName))
	return false;

    SrvCfgIfaceLst.append(new TSrvCfgIface(ifaceName));


    ParserOptStack.append(new TSrvParsGlobalOpt(*ParserOptStack.getLast()));
    SrvCfgAddrClassLst.clear();
    ClientLst.clear();

    return true;
}
