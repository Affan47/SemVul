IDirectFBInputDevice_GetXY( IDirectFBInputDevice *thiz,
                            int                  *x,
                            int                  *y )
{
     DIRECT_INTERFACE_GET_DATA(IDirectFBInputDevice)

     if (!x && !y)
          return DFB_INVARG;

     if (x)
          *x = data->axis[DIAI_X];

     if (y)
          *y = data->axis[DIAI_Y];

     return DFB_OK;
}
