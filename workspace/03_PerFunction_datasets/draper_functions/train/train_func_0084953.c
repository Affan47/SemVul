Write_Tree(arbre *tree)
{

  char *s;
  int i;

  s=(char *)mCalloc(T_MAX_LINE,sizeof(char));

  s[0]='(';

  i = 0;
  while((!tree->noeud[tree->n_otu+i]->v[0]) ||
	(!tree->noeud[tree->n_otu+i]->v[1]) ||
	(!tree->noeud[tree->n_otu+i]->v[2])) i++;

  R_wtree(tree->noeud[tree->n_otu+i],tree->noeud[tree->n_otu+i]->v[0],s,tree);
  R_wtree(tree->noeud[tree->n_otu+i],tree->noeud[tree->n_otu+i]->v[1],s,tree);
  R_wtree(tree->noeud[tree->n_otu+i],tree->noeud[tree->n_otu+i]->v[2],s,tree);

  s[(int)strlen(s)-1]=')';
  s[(int)strlen(s)]=';';


  return s;
}
