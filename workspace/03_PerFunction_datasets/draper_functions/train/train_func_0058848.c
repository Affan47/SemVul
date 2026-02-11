show(void)
{
  if (mapped()==MSFalse)
   {
     if (comboBox()->selectionMode()==MSSingle)
      {
	MSString buffer;
	comboList()->setSelectedRowFrom(comboBox()->formatOutput(buffer));
      }
     comboList()->show();
     map();
     XFlush(display());
     raise();
     grab();
   }
}
