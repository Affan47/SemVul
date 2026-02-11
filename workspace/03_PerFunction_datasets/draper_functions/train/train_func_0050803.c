updateTitle(void)
{
  V v = (model()!=0)?((AplusModel*)model())->aplusVar():0;

  if (v!=0)
   {
     AplusSlotEntryField *fld;
     A                str;

     MSBoolean wasFrozen=freezeIfUnfrozen();
     for (int i = 0; i < fields().length(); i++)
      {
	fld = (AplusSlotEntryField *)(MSWidget *) fields()(i);
	str = itemLabel(i);
        if(isNull(str)==MSFalse)
	 {
  	   fld->label((char *)str->p);
	   dc(str);
	 }
	fld->labelFont(titleFont(i));
	fld->labelForeground(titleColor(i));
      }
     alignLabels();
     unfreezeIfUnfrozen(wasFrozen);
   }
  MSCompositeFieldBox::updateTitle();
}
