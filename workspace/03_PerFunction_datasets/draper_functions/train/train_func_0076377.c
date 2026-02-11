trace(IntSequence&out,const Permutation&per)const
{
TL_RAISE_IF(out.size()!=n,
"Wrong size of output sequence in Equivalence::trace");
TL_RAISE_IF(per.size()!=numClasses(),
"Wrong permutation for permuted Equivalence::trace");
int i= 0;
for(int iclass= 0;iclass<numClasses();iclass++){
const_seqit itper= find(per.getMap()[iclass]);
for(int j= 0;j<(*itper).length();j++,i++)
out[i]= (*itper)[j];
}
}
