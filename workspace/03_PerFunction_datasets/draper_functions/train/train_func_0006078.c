ati128_set_blittingflags( ATI128DriverData *adrv,
                               ATI128DeviceData *adev,
                               CardState        *state )
{
     if (adev->v_blittingflags)
          return;

     if (state->blittingflags & DSBLIT_SRC_COLORKEY) {
          adev->ATI_color_compare = (1 << 24) | 5;
     }
     else {
          adev->ATI_color_compare = 0;
     }

     adev->blittingflags = state->blittingflags;
     adev->v_blittingflags = 1;
}
