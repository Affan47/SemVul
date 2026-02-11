FormatCubePosition(char *sz, cubeinfo * pci)
{

    if (pci->fCubeOwner == -1)
        sprintf(sz, _("Centered %d-cube"), pci->nCube);
    else
        sprintf(sz, _("Player %s owns %d-cube"), ap[pci->fCubeOwner].szName, pci->nCube);

    return sz;

}
