DeviceChanged(dev_t thisdevice)

{
if (thisdevice == ROOTDEVICE)
   {
   return false;
   }
else
   {
   Verbose("Device change from %d to %d\n",ROOTDEVICE,thisdevice);
   return true;
   }
}
