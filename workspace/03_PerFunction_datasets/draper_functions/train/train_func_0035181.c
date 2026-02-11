receiveEvent(MSEvent& event_)
{
  const MSSymbol& eventType = event_.type();

  if (eventType==AplusEvent::symbol())
    {
      if (dbg_tmstk) cout << "Received UpdateEvent in AplusArray"  << endl;
      AplusEvent *ave = (AplusEvent *) &event_;
      V v     = ((AplusModel *)model())->aplusVar();
      A index = ave->index();
      A pick  = ave->pick();
      I ravel = ave->ravel();;
      update(v,index, pick, ravel);
    }
  else if (eventType==AplusVerifyEvent::symbol())
    {
      if (dbg_tmstk) cout << "Received VerifyEvent in AplusArray"  << endl;

      AplusVerifyEvent *ave = (AplusVerifyEvent *) &event_;
      ave->result(verifyData(ave->aplusVar(), ave->a()));
    }
  else if (eventType==AplusUpdateDataEvent::symbol())
    {
      if (dbg_tmstk) cout << "Received UpdateDataEvent in AplusArray"  << endl;
      V v = ((AplusModel *)model())->aplusVar();
      if (v)
	{
	  AVariableData *varData = ::pAVarDataFromV(v);
	  if (varData)
	    {
	      columnWidth(varData->colWidth());
	      redraw();
	    }
	}
    }
  else if (eventType==AplusUpdateTitleEvent::symbol())
    {
      if (dbg_tmstk) cout << "Received UpdateTitleEvent in AplusArray"  << endl;
      updateTitle();
    }
}
