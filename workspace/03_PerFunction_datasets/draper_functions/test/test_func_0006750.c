printOpen()
{
  MSBoolean status=MSTrue;
  MSString file(fileName());
  if (outputMode()==EPS) file.change(".ps",".eps",0,1);
  if (outputMode()==PPM) file.change(".ps",".ppm",0,1);
  pout.open(file);
  if (pout.fail()==ios::failbit)
   {
     MSMessageLog::warningMessage("Error: opening file %s\n",file.string());
     status=MSFalse;
   }
  return status;
}
