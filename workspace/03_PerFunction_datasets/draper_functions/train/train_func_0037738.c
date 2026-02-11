tbbtindx(TBBT_NODE * root, int32 indx)
{
  TBBT_NODE  *ptr = root;


  if (NULL == ptr || indx < 1)
    return (NULL);


  while (ptr != NULL && indx != ((int32) LeftCnt(ptr)) + 1 )
    {
      if (indx <= (int32) LeftCnt(ptr))
        {
#if 0
          indx -= LeftCnt(ptr);
#endif
          ptr = ptr->Lchild;
        }
      else if (HasChild(ptr, RIGHT))
        {

          indx -= (int32)(LeftCnt(ptr) + 1);
          ptr = ptr->Rchild;
        }
      else
        return (NULL);
    }
  return (ptr);
}
