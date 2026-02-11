writeMpsNative(const char *filename,
				   const char ** rowNames,
				   const char ** columnNames,
				   int formatType,
				   int numberAcross,
				   double objSense,
				   int numberSOS,
				   const CoinSet * setInfo ) const
{
   const int numcols = getNumCols();
   char* integrality = new char[numcols];
   bool hasInteger = false;
   for (int i = 0; i < numcols; ++i) {
      if (isInteger(i)) {
	 integrality[i] = 1;
	 hasInteger = true;
      } else {
	 integrality[i] = 0;
      }
   }


   double * objective = new double[numcols];
   memcpy(objective,getObjCoefficients(),numcols*sizeof(double));

   double locObjSense = (objSense == 0 ? 1 : objSense);
   if(getObjSense() * locObjSense < 0.0) {
     for (int i = 0; i < numcols; ++i)
       objective [i] = - objective[i];
   }

   CoinMpsIO writer;
   writer.setInfinity(getInfinity());
   writer.passInMessageHandler(handler_);
   writer.setMpsData(*getMatrixByCol(), getInfinity(),
		     getColLower(), getColUpper(),
		     objective, hasInteger ? integrality : 0,
		     getRowLower(), getRowUpper(),
		     columnNames,rowNames);
   double objOffset=0.0;
   getDblParam(OsiObjOffset,objOffset);
   writer.setObjectiveOffset(objOffset);
   delete [] objective;
   delete[] integrality;
   return writer.writeMps(filename, 1 , formatType, numberAcross,
			  NULL,numberSOS,setInfo);
}
