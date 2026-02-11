i810ovlOnOff( I810DriverData *idrv,
              I810DeviceData *idev,
              bool            on )
{
     if (on)
          idrv->oregs->ov0cmd |= 1;
     else
          idrv->oregs->ov0cmd &= ~1;

     update_overlay( idrv, idev );
}
