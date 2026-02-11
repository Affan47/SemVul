SetUpdateExtent(int piece, int numPieces, int ghostLevel)
{
  if(SDDP* sddp = this->TrySDDP("SetUpdateExtent"))
    {


    sddp->SetUpdateExtent
      (sddp->GetOutputInformation()->GetInformationObject
       (this->GetPortNumber()), piece, numPieces, ghostLevel);
    }
}
