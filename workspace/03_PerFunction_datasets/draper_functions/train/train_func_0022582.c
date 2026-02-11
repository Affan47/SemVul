operator<<(ostream& os,const MSResourceCodeSet& rCodeSet_)
{
  os <<"MSResourceCodeSet: " ;
  int num=rCodeSet_.numberOfElements();
  os << num << " elements:<" ;
  for (int i=0; i<num; ++i)
   {
     os << rCodeSet_._stringVector.elementAt(i);
     if (i<num-1) os <<',';
   }
  os << '>' << endl;
  return os;
}
