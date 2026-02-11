calcQuickDistMatForAll(ofstream* clustalFile, ofstream* phylipFile,
                                  ofstream* nexusFile, ofstream* pimFile, ofstream* distFile,
                                  clustalw::Alignment* alignPtr)
{
    int overspill = 0;
    bool _DNAFlag = clustalw::userParameters->getDNAFlag();

    overspill = calcQuickDistMatForSubSet(clustalFile, phylipFile, nexusFile, alignPtr);

    if (pimFile && clustalw::userParameters->getOutputPim())
    {
        verbose = false;
        if (_DNAFlag)
        {
            calcPercIdentity(pimFile, alignPtr);
        }
        else
        {
            calcPercIdentity(pimFile, alignPtr);
        }
    }


    if (distFile && clustalw::userParameters->getOutputTreeDistances())
    {
        verbose = false;
        if (_DNAFlag)
        {
            overspill = dnaDistanceMatrix(distFile, alignPtr);
        }
        else
        {
            overspill = protDistanceMatrix(distFile, alignPtr);
        }
        distanceMatrixOutput(distFile, quickDistMat.get(),
                             alignPtr);
    }
    return overspill;
}
