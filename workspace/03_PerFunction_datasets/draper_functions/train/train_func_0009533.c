selectedNodeA(void) const
{
  TreeModelCursor cursor(selectedNode());

  if (cursor.isValid()==MSFalse)
    {
      return aplus_nl;
    }

  MSUnsignedLongVector nodePath(1,(unsigned long)cursor.element().symbol());
  S sym;

  while (cursor.setToParent()==MSTrue)
    {
      sym = cursor.element().symbol();


      if (sym==0)
	{
	  break;
	}

      nodePath << (unsigned long)sym;
    }

  I pathLen=nodePath.length();
  if (pathLen==0)
    {
      return aplus_nl;
    }

  A svPath = gv(Et,pathLen);
  P p; p.i=svPath->p;

  for (I i=0; i<pathLen; ++i)
    {
      p.a[i]=(A)MS(nodePath(pathLen-i-1));
    }

  return svPath;
}
