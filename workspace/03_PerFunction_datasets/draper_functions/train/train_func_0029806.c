change(const char *pPattern,unsigned patternLen,
                                       const char *pReplacement,unsigned replacementLen,
                                       unsigned startPos,unsigned numChanges)
{
  MSStringBuffer *result=this;

  unsigned count=0;


  Occurrence  head       =Occurrence(0);
  Occurrence *pOccurrence=&head;


  while (count<numChanges)
   {
     if ((startPos=indexOf(pPattern,patternLen,startPos))<length())
      {

	count++;
	pOccurrence=pOccurrence->pNext=new Occurrence(startPos);
	startPos+=patternLen;
      }
     else break;
   }

  if (count!=0)
   {


     pOccurrence->pNext=new Occurrence(length()+1);

     pOccurrence=head.pNext;
     const char *pSource=contents()+pOccurrence->pos;


     if (patternLen!=replacementLen)
      {
	unsigned newLen=length();
	if (patternLen>replacementLen) newLen-=checkMultiplication(patternLen-replacementLen,count);
	else newLen=checkAddition(newLen,checkMultiplication(replacementLen-patternLen,count));


	result=newBuffer(contents(),pSource-contents(),
			 0,newLen-(pSource-contents()),
			 0,0,
			 0);
      }
     else
      {
	if (useCount()==1) addRef();
	else result=newBuffer(contents(),length());
      }

     char *pDest=result->contents()+(pOccurrence->pos);


     while (count--)
      {
	unsigned previousPos=pOccurrence->pos;
	pOccurrence=pOccurrence->pNext;
	memcpy(pDest,pReplacement,replacementLen);
	pDest  +=replacementLen;
	pSource+=patternLen;

	unsigned n=(pOccurrence->pos-previousPos)-patternLen;
	if (patternLen!=replacementLen) memcpy(pDest,pSource,n);
	pDest  +=n;
	pSource+=n;
      }
   }
  else addRef();
  return result;
}
