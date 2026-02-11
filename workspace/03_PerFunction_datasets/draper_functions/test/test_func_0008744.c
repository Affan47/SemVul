operator<(const IntSequence&s)const
{
int len= min(size(),s.size());

int i= 0;
while(i<len&&operator[](i)==s[i])
i++;
return(i<s.size()&&(i==size()||operator[](i)<s[i]));
}
