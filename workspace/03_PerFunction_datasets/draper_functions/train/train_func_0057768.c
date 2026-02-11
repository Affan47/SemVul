SetDeviceAddress(u8 Val)
{
  u32 i;
  u32 nEP = Device_Table.Total_Endpoint;


  for (i = 0; i < nEP; i++)
  {
    _SetEPAddress((u8)i, (u8)i);
  }
  _SetDADDR(Val | DADDR_EF);
}
