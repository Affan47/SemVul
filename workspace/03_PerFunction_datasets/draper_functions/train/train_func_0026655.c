add(Int4 ii,Int4 jj)
{
  if (tete == 0 ) {
    cerr << "SetOfEdges4::add\n plus de tete de liste \n" << endl;
    MeshError(888);}

  Int4 h;
  Int4 n = tete[ h = Abs( ii ) % nx ];
  while (n >= 0)
   if (ii == Edges[n].i && jj == Edges[n].j)
            return n;
   else n = Edges[n].next;
  if (nbax <=NbOfEdges ) {
    cerr << " SetOfEdges4::add\noverflow de la pile "  << nbax << " " << NbOfEdges << endl;
    MeshError(888);}

   Edges[NbOfEdges].i=ii;
   Edges[NbOfEdges].j=jj;
   Edges[NbOfEdges].next= tete[h];
   tete[h] = NbOfEdges;
   return NbOfEdges ++;
}


}
