getWeightsForProfileAlignUPGMA(Alignment* alignPtr, DistMatrix* distMat,
                             string* p1TreeName, vector<int>* p1Weights, string* p2TreeName,
                    vector<int>* p2Weights, int numSeqs, int profile1NumSeqs, bool useTree1,
                    bool useTree2, bool* success)
{
    int status = 0;

    if(useTree1)
    {

        Tree groupTree1;
        if (profile1NumSeqs >= 2)
        {
            status = groupTree1.readTree(alignPtr, p1TreeName->c_str(), 0, profile1NumSeqs);
            if (status == 0)
            {
                *success = false;
                return;
            }
        }
        groupTree1.calcSeqWeights(0, profile1NumSeqs, p1Weights);

        if (profile1NumSeqs >= 2)
        {
            groupTree1.clearTree(NULL);
        }
    }
    else
    {
        if (profile1NumSeqs >= 2)
        {
            RootedGuideTree guideTree;
            generateTreeFromDistMatUPGMA(&guideTree, distMat, alignPtr, 1, profile1NumSeqs,
                                         p1TreeName, success);
            guideTree.calcSeqWeights(0, profile1NumSeqs, p1Weights);
        }
    }

    if(useTree2)
    {
        Tree groupTree2;
        if (numSeqs - profile1NumSeqs >= 2)
        {
            status = groupTree2.readTree(alignPtr, p2TreeName->c_str(),
                                         profile1NumSeqs, numSeqs);
            if (status == 0)
            {
                *success = false;
                return;
            }
        }
        groupTree2.calcSeqWeights(profile1NumSeqs, numSeqs, p2Weights);

        if (numSeqs - profile1NumSeqs >= 2)
        {
            groupTree2.clearTree(NULL);
        }
    }
    else
    {
        if(numSeqs - profile1NumSeqs >= 2)
        {
            RootedGuideTree guideTree;
            generateTreeFromDistMatUPGMA(&guideTree, distMat, alignPtr, profile1NumSeqs + 1,
                                         numSeqs - profile1NumSeqs, p2TreeName, success);
            guideTree.calcSeqWeights(profile1NumSeqs, numSeqs, p2Weights);
        }
    }

    if (userParameters->getNewTree1File() || userParameters->getNewTree2File())
    {
        *success = false;
        return;
    }

    MSA* msaObj = new MSA();

    int count = msaObj->calcPairwiseForProfileAlign(alignPtr, distMat);

    delete msaObj;

    if (count == 0)
    {
        *success = false;
        return;
    }


    distMat->makeSimilarityMatrix();

    *success = true;

}
