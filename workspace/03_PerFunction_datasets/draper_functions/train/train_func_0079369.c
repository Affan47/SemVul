update(V v_,A,A pick_,I)
{
  V oldV = (model()!=0)?((AplusModel*)model())->aplusVar():0;

  if (pick_!=0)
   {
     if (QA(pick_))
      {
	A pick=(A)gpix(pick_,(A)v_->a);
	if (pick!=0&&QA(pick)&&pick->t==It&&pick->r<=1)
	 {
	   if (pick->r==1)
	    {
	      if (pick->n>0) for (int i=0;i<pick->n;i+=2)updateValue((int)pick->p[i+1]);
	      else updateValues();
	    }
	   else
	    {
	      if (pick->p[0]==1) updateValues();
	      else if (v_==oldV) updateData();
	    }
	 }
	else if (pick==0) cerr<<"action: pick assignment error in update."<<endl;
        else cerr<<"action: pick assignment error in update."<<endl;
	if (pick!=0) dc(pick);
      }
     else cerr<<"action: pick assignment error in update."<<endl;
   }
  else if (v_==oldV) updateData();
}
