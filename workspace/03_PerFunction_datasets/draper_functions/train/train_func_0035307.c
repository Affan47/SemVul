cyrusdb_done()
{
    int i;

    for(i=0; cyrusdb_backends[i]; i++) {
	(cyrusdb_backends[i])->done();
    }
}
