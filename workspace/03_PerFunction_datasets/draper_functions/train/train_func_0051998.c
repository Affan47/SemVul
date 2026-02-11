AaffPreprocess (t_pAaffPreprocess pPreprocess, unsigned char *pDataIn, unsigned int DataLenIn, unsigned char *pDataOut, uint DataLenOut)
{

   int                rc;
   uLongf             LenOut;


   pPreprocess->Zero       = false;
   pPreprocess->Compressed = false;


   pPreprocess->Zero = UtilIsZero (pDataIn, DataLenIn);
   if (pPreprocess->Zero)
      return NO_ERROR;


   LenOut = DataLenOut;
   rc = compress2 ((Bytef *)pDataOut, &LenOut, (Bytef *)pDataIn, DataLenIn, CONFIG (AffCompression));
   pPreprocess->DataLenOut = LenOut;
   if (rc != Z_OK)
   {
      if (rc != Z_BUF_ERROR)
         LOG_ERROR ("compress2 returned %d", rc)
      return NO_ERROR;
   }

   pPreprocess->Compressed = (LenOut < DataLenIn);

   return NO_ERROR;
}
