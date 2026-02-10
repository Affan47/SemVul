FreeKMeansResult(bisecting_kmeans_result_t **prResult_p)
{
    int iAux;
    CKFREE((*prResult_p)->piNObjsPerCluster);
    for (iAux=0; iAux<(*prResult_p)->iNClusters; iAux++) {
        CKFREE((*prResult_p)->ppiObjIndicesPerCluster[iAux]);
        CKFREE((*prResult_p)->ppdClusterCenters[iAux]);
    }
    CKFREE((*prResult_p)->ppiObjIndicesPerCluster);
    CKFREE((*prResult_p)->ppdClusterCenters);
    (*prResult_p)->iNClusters = 0;
    (*prResult_p)->iDim = 0;
    CKFREE(*prResult_p);
}
