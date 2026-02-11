GetDocumentStatus(HtNNTP_Response &r)
{


   HtNNTP::DocStatus returnStatus=Document_not_found;
   int statuscode;

   statuscode=r.GetStatusCode();

   if(statuscode==200)
   {
	    returnStatus = Document_ok;
   }


   return returnStatus;

}
