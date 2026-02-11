httpFetch( void *ptr, size_t size, size_t nmemb, void *pData )
{
   vector<char>* pBuf = static_cast< vector<char>* >(pData);
   if ( pBuf == NULL )
      return 0;

   size_t realsize = size * nmemb;
   size_t startSize = pBuf->size();

   pBuf->resize(startSize + realsize);
   memcpy( &((*pBuf)[startSize]), ptr, realsize );

   return realsize;
}
