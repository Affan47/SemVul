popNameSpace()
{

  for (int i = 0;i < typeList->Count(); i++)
    {
    VrmlNodeType *nodeType = typeList->Pop();

    if (nodeType == NULL)
      {
      break;
      }
    else
      {


      delete nodeType;
      }
    }
}
