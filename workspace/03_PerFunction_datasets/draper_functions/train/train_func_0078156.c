print(Printer &P)const
{
  for(int j=0;j<v.size();j++)
    {
      P.printFieldElement(v[j]);
      P.printString(" ");
    }
  P.printNewLine();
}
