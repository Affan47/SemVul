GroupDetach(char *c, Object *in)
{
    char *groupname;
    int n, k, limit;
    PGassign *index;
    dpgraphstat *hostentry;

    if(_dxd_exRemoteSlave)
        return(OK);

    if(!in[0]) {
        DXSetError (ERROR_BAD_PARAMETER, "#10200", "group name");
        return (ERROR);
    }

    n = 0;
    while(DXExtractNthString(in[0], n, &groupname)) {
        for (k = 0, limit = SIZE_LIST(_dxd_pgassign); k < limit; ++k) {
            index = FETCH_LIST(_dxd_pgassign, k);
            if(!strcmp(index->pgname, groupname)) {
                hostentry = FETCH_LIST(_dxd_dpgraphstat, index->hostindex);
                if(hostentry) {
                    if(!hostentry->error)
                        index->hostindex = UpdateWorkers(
				  hostentry->prochostname,
                                  hostentry->procusername, NULL, 0);
                }
                _dxf_ExGVariableSetStr(index->pgname, NULL);
                _dxf_ExCacheFlush(FALSE);
                DXFree(index->pgname);
                DELETE_LIST(PGassign, _dxd_pgassign, k);
                break;
            }
        }
        n++;
    }
    return(OK);
}
