calcWeights(vector<int>* seqWeights)
{
    vector<float> weights;
    int sizeSeqWeights = seqWeights->size();
    weights.resize(sizeSeqWeights, 0.0);

    doWeightCalc(0.0, &weights, root);

    for(int i = 0; i < sizeSeqWeights; i++)
    {
        (*seqWeights)[i] = static_cast<int>(weights[i] * 100);
    }
}
