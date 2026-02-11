readTreeAndCalcWeightsNJ(Tree* groupTree, Alignment* alignPtr,
                                        DistMatrix* distMat, string* treeName,
                                        vector<int>* seqWeights, int fSeq, int nSeqs)
{
    int status = 0;
    if (nSeqs >= 2)
    {
        status = groupTree->readTree(alignPtr, treeName->c_str(), fSeq - 1, nSeqs);
        if (status == 0)
        {
            return status;
        }
    }

    groupTree->calcSeqWeights(fSeq - 1, nSeqs, seqWeights);

    status = groupTree->calcSimilarities(alignPtr, distMat);

    return status;
}
