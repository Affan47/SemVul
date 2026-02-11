AddRadicalToMetal( int *tot_st_cap, int *tot_st_flow, ICHICONST SRM *pSrm, BN_STRUCT *pBNS, ALL_TC_GROUPS *pTCGroups )
{
    int iG0 = pTCGroups->nGroup[TCG_MeFlower0];
    int iG1 = pTCGroups->nGroup[TCG_MeFlower1];
    int iG2 = pTCGroups->nGroup[TCG_MeFlower2];
    int iG3 = pTCGroups->nGroup[TCG_MeFlower3];
    int n   = (iG0>=0) + (iG1>=0) + (iG2>=0) + (iG3>=0);
    int vG0, vG1, vG2, vG3;
    BNS_VERTEX *pG0=NULL, *pG1=NULL, *pG2=NULL, *pG3=NULL;

    if ( pTCGroups->num_metal_atoms &&
         pSrm->bMetalAddFlower      &&
         *tot_st_cap % 2            &&
         n == 4 ) {
        vG0 = pTCGroups->pTCG[iG0].nVertexNumber;
        vG1 = pTCGroups->pTCG[iG1].nVertexNumber;
        vG2 = pTCGroups->pTCG[iG2].nVertexNumber;
        vG3 = pTCGroups->pTCG[iG3].nVertexNumber;

        pG0 = pBNS->vert+vG0;
        pG1 = pBNS->vert+vG1;
        pG2 = pBNS->vert+vG2;
        pG3 = pBNS->vert+vG3;


        pG3->st_edge.cap  ++;
        pG3->st_edge.cap0 ++;
        (*tot_st_cap)     ++;
        return 1;
    }
    return 0;
}
