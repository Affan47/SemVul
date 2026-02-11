daptoplevel(CDFnode* node)
{
    if(node->container == NULL
       || node->container->nctype != NC_Dataset) return FALSE;
    return TRUE;
}
