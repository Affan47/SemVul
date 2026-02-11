activate(void)
{
  MSActionButton *entry=activeButton();
  unsigned pos = buttons().indexOf((unsigned long)(MSWidget*)entry);

  if (entry!=0)
   {

     P p; p.i=((AplusModel*)model())->data();
     A as=p.a[0];
     A attr=(A)as->p[pos];
     A val=p.a[1];
     A pick=(A)gs(Et);
     *pick->p=(I)attr;
     A data=(A)val->p[pos];
     (void)callAset(((AplusModel*)model())->aplusVar(),(A)ic(data),0,pick);
     dc(pick);
   }
}
