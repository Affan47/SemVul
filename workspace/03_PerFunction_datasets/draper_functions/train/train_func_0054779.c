deletePrivateData()
{

  if (dfile == NULL)
      return makeOFCondition(OFM_dcmdata,22,OF_error,"No file loaded yet!");

  DcmStack stack;
  DcmObject *dobj = NULL;
  DcmTagKey tag;
  OFCondition status = dset->nextObject(stack, OFTrue);
  while (status.good())
  {
      dobj = stack.top();
      tag = dobj->getTag();
      if (tag.getGroup() & 1)
      {
          stack.pop();
          delete OFstatic_cast(DcmItem *, (stack.top()))->remove(dobj);
      }
      status = dset->nextObject(stack, OFTrue);
  }
  return EC_Normal;
}
