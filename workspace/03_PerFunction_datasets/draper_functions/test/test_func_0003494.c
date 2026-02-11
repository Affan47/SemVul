computeSortingMap(const IntSequence&s)
{
IntSequence srt(s);
srt.sort();
IntSequence flags(s.size(),0);

for(int i= 0;i<s.size();i++){
int j= 0;
while(j<s.size()&&(flags[j]||srt[j]!=s[i]))
j++;
TL_RAISE_IF(j==s.size(),
"Internal algorithm error in Permutation::computeSortingMap");
flags[j]= 1;
permap[i]= j;
}
}
