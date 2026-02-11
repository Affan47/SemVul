Record()
{
  nb_rec++;
  n += sizeof(long);
  f->seekg(n);
  f->read((char*)&l,sizeof(l));
  if (!f->good()) Error(3);
  i=j= n+sizeof(l);
  n +=   l + sizeof(l) ;
  if (verbosity>9)
  cout << " Read  rec end =" << n << " l=  " << l
       << " current= " << j << " begin= " << i << endl;
  return l;
}
