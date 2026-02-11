cdk_subpkt_add (cdk_subpkt_t root, cdk_subpkt_t node)
{
  cdk_subpkt_t n1;

  if (!root)
    return CDK_Inv_Value;
  for (n1 = root; n1->next; n1 = n1->next)
    ;
  n1->next = node;
  return 0;
}
