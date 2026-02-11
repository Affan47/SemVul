prefixIsFree(SPtr<TIPv6Addr> x)
{
    SPtr<TAddrClient> client;
    SPtr<TAddrIA> pd;
    SPtr<TAddrPrefix> prefix;

    firstClient();
    while (client = getClient()) {
	      client->firstPD();
	      while (pd = client->getPD()) {
	          pd->firstPrefix();
	          while (prefix = pd->getPrefix()) {
		            if (*prefix->get()==*x)
		                return false;
	          }
	      }
    }


    return true;
}
