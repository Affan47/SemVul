computeTrigramBackoff(int wd1,int wd2,int wd3) const
{
    logger << DEBUG << "computing P( ["<<vocabDecode.find(wd3)->second<< "] | ["<<vocabDecode.find(wd1)->second<<"] ["<<vocabDecode.find(wd2)->second<<"] )"<<endl;


    std::map<TrigramKey,float>::const_iterator trigramIt =trigramMap.find(TrigramKey(wd1,wd2,wd3));
    if(trigramIt!=trigramMap.end())
    {
	logger << DEBUG << "trigram ["<<vocabDecode.find(wd1)->second<< "] ["<<vocabDecode.find(wd2)->second<< "] ["<<vocabDecode.find(wd3)->second<< "] exists" <<endl;
	logger << DEBUG << "returning "<<trigramIt->second <<endl;
	return trigramIt->second;
    }


    std::map<BigramKey,ARPAData>::const_iterator bigramIt =bigramMap.find(BigramKey(wd1,wd2));
    if(bigramIt!=bigramMap.end())
    {
	logger << DEBUG << "bigram ["<<vocabDecode.find(wd1)->second<< "] ["<<vocabDecode.find(wd2)->second<< "] exists" <<endl;
	float prob = bigramIt->second.logAlfa + computeBigramBackoff(wd2,wd3);
	logger << DEBUG << "returning "<<prob<<endl;
	return prob;
    }


    logger << DEBUG << "no bigram w1,w2 exist" <<endl;
    float prob = computeBigramBackoff(wd2,wd3);
    logger << DEBUG << "returning "<<prob<<endl;
    return prob;

}
