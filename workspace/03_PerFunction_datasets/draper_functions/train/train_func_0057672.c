addDelimiter(int col_)
{
  if (delimiterVector().indexOf(col_)==delimiterVector().length())
   {
     _delimiterVector.append(col_);
     _delimiterVector.sortUp();
     delimiterChangeNotify();
   }
}
