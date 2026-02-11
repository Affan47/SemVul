SetUpdateExtentToWholeExtent()
{
  if(SDDP* sddp = this->TrySDDP("SetUpdateExtentToWholeExtent"))
    {


    sddp->SetUpdateExtentToWholeExtent
      (sddp->GetOutputInformation()->GetInformationObject
       (this->GetPortNumber()));
    }
}
