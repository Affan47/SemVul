addOutputIndex(vector<int>* outputIndexToAdd)
{

    outputIndex.clear();

    if((int)outputIndexToAdd->size() == numSeqs)
    {

        outputIndex = *outputIndexToAdd;
        return true;
    }
    else
    {
        clearAlignment();
        return false;
    }

}
