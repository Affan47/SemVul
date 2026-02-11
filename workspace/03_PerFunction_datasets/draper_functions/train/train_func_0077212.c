translate( const MSKeyPress &keyTranslation_,MSWidget * widget_) const
{
  if (_pListHead!=0)
   {
     MSNodeItem *hp=_pListHead;
     MSNodeItem *np=hp;

     if (hp!=hp->next())
      {
	MSKeyTableData        *data;

	while ((np=np->next())!=hp)
	  {
	    data=(MSKeyTableData *) np->data();
	    if (data->process(keyTranslation_,widget_)==MSTrue)
	      return MSTrue;
	  }
      }
   }
     return MSFalse;
}
