operator<<( ostream &output, const SchedulerEntry &s)
{
   output << s.ScheduleUrl;

   if (s.debug < 3) return output;


   output << " (ID: " << s.IDSchedule << " / "
      << "IDServer: " << s.IDServer << " / ";

   std::string Status("");

   s.RetrieveStatus(Status);

   if (!Status.length())
      Status = "Not yet assigned";

   std::string Domain("");

   s.RetrieveDomain(Domain);

   if (!Domain.length())
      Domain = "Not yet assigned";

   output << (int) s.Status << " - " << Status << " / "
      << (int) s.Domain << " - " << Domain << " )";

   if (s.server)
      output << " Server: " << s.server->host() << ":" << s.server->port();

   return output;
}
