Bionj(matrix *mat)
{
  int x,y,i;
  double vxy,lx,ly,lamda,score;

  For(i,mat->tree->n_otu)
    mat->tip_node[i] = mat->tree->noeud[i];


  while(mat->r > 3)
    {
      x = y = 0;
      vxy = .0;
      score = .0;
      Compute_Sx(mat);
      Best_Pair(mat,&x,&y,&score);
      vxy=Variance(mat,x,y);
      lx=Br_Length(mat,x,y);
      ly=Br_Length(mat,y,x);
      lamda=Lamda(mat,x,y,vxy);
      Update_Mat(mat,x,y,lx,ly,vxy,lamda);
      Update_Tree(mat,x,y,lx,ly,score);
    }

  Finish(mat);
  i=0;

  Init_Tree_Edges(mat->tree->noeud[0],
		  mat->tree->noeud[0]->v[0],
		  mat->tree,&i);
}
