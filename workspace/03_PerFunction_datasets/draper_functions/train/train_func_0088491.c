ConvertTotalInputToPortConnection(
  int ind, int &port, int &conn)
{
  port = 0;
  conn = 0;
  while (ind && port < this->GetNumberOfInputPorts())
    {
    int pNumCon;
    pNumCon = this->GetNumberOfInputConnections(port);
    if (ind >= pNumCon)
      {
      port++;
      ind -= pNumCon;
      }
    else
      {
      return;
      }
    }
}
