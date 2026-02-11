KillGraph (char *c, Object *in)
{
    if (!_dxf_ExGQAllDone ()) {
	*_dxd_exKillGraph = TRUE;
        _dxf_ExDistributeMsg(DM_KILLEXECGRAPH,
                             (Pointer)_dxd_exContext->graphId, 0, TOPEERS);
    }
    return (OK);
}
