determined (List_Node *ptr)
{
  for (char *temp = ptr->keysig; *temp; temp++)
    Key_List::determined_[(int) *temp] = 1;
}
