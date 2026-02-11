freenccachenode(NCDAPCOMMON* nccomm, NCcachenode* node)
{
    if(node == NULL) return;
    oc_data_free(nccomm->oc.conn,node->content);
    oc_data_free(nccomm->oc.conn,node->content);
    dcefree((DCEnode*)node->constraint);
    freecdfroot34(node->datadds);
    nclistfree(node->vars);
    nullfree(node);
}
