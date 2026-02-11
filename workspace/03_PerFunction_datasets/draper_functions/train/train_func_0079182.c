join(void **iret)
{
  int ret;
  ret=doJoin(iret);
  if (ret)
    return(ret);

  removeThreadFromMap(myThread);


  return(0);
}
