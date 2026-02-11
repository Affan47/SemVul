create()
{
   pbcp_application result(static_cast<bcp_application*>(new bcp_implementation()));
   return result;
}
