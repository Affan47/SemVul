deletevar(v)
vari *v;
{ if (root.n==0) return;
  if (v!=NULL) v->stat = STEMPTY;
  if ((v==NULL) || (v==viptr(&root,root.n-1)))
  { root.n--;
    lfwptr -= ((vari *)viptr(&root,root.n))->bytes;
  }
}
