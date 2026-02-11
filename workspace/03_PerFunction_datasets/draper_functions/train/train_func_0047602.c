M_Write(void)
{
  if(!MetaObject::M_Write())
    {
    METAIO_STREAM::cout << "MetaScene: M_Write: Error parsing file" << METAIO_STREAM::endl;
    return false;
    }

  return true;
}
