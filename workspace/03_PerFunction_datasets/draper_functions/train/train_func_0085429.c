SendMsg(struct XObj *xobj,int TypeMsg)
{
  int i;

  for (i=0; i <= TabCObj[TabIdObj[xobj->id]].NbCase; i++)
    if (TabCObj[TabIdObj[xobj->id]].LstCase[i] == TypeMsg)
    {

      ExecBloc(&TabIObj[TabIdObj[xobj->id]][i]);
    }
}
