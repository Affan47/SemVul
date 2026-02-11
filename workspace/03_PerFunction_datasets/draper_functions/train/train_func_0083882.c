process_request (ACE_TCHAR *request)
{
  ACE_TRACE("ACE_Service_Manager::process_request");
  ACE_TCHAR *p;


  for (p = request;
       (*p != '\0') && (*p != '\r') && (*p != '\n');
       p++)
    {
      continue;
    }

  *p = '\0';

  if (ACE_OS::strcmp (request, ACE_TEXT ("help")) == 0)
    {

      this->list_services ();
    }
  else if (ACE_OS::strcmp (request, ACE_TEXT ("reconfigure") )== 0)
    {

      this->reconfigure_services ();
    }
  else
    {


      ACE_Service_Config_Guard guard (ACE_Service_Config::global ());
      ACE_Service_Config::process_directive (request);
    }


}
