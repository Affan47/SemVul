createCycle(void)
{
  V v = (model()!=0)?((AplusModel*)model())->aplusVar():0;
  A a = (model()!=0)?((AplusModel*)model())->a():aplus_nl;
  ACycleFunction *cycleFunc = AplusModel::getCycleFunc(v);
  MSUnsignedLongVector uv;

  if (v!=0)
   {
     if (cycleFunc && cycleFunc->func()!=0)
      {
	A colors = cycleFunc->invoke(v,a);
	A pixelColors = (isNull(colors)==MSFalse) ? convertToPixels(this,colors) : colors;
	if (isNull(pixelColors)==MSFalse)
	 {
	   for (unsigned i = 0; i < pixelColors->n; i++)
	   uv << (unsigned long) pixelColors->p[i];
	   dc(pixelColors);
	 }
	cycleColors(uv);
      }
   }

  MSEntryFieldPlus::createCycle();
}
