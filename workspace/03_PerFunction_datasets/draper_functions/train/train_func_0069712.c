i830SetState( void *drv, void *dev,
              GraphicsDeviceFuncs *funcs,
              CardState *state, DFBAccelerationMask accel )
{
     switch (accel) {
          default:
               D_BUG("unexpected drawing/blitting function");
     }

     state->mod_hw = 0;
}
