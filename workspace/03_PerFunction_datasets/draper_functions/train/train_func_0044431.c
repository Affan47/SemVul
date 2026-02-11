Make_Node_Light(node *n)
{

  if(n->v) return;

  n->v     = (node **)mCalloc(3,sizeof(node *));
  n->l     = (double *)mCalloc(3,sizeof(double));
  n->b     = (edge **)mCalloc(3,sizeof(edge *));
  n->name  = (char *)mCalloc(T_MAX_NAME,sizeof(char));
  n->score = (double *)mCalloc(3,sizeof(double));

  Init_Node_Light(n);

}
