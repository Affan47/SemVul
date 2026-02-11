IDirectFBScreen_SetEncoderConfiguration( IDirectFBScreen              *thiz,
                                         int                           encoder,
                                         const DFBScreenEncoderConfig *config )
{
     DFBResult              ret;
     DFBScreenEncoderConfig patched;

     DIRECT_INTERFACE_GET_DATA(IDirectFBScreen)

     if (!config || (config->flags & ~DSECONF_ALL))
          return DFB_INVARG;

     if (! (data->description.caps & DSCCAPS_ENCODERS))
          return DFB_UNSUPPORTED;

     if (encoder < 0 || encoder >= data->description.encoders)
          return DFB_INVARG;


     ret = dfb_screen_get_encoder_config( data->screen, encoder, &patched );
     if (ret)
          return ret;


     ret = PatchEncoderConfig( &patched, config );
     if (ret)
          return ret;


     return dfb_screen_set_encoder_config( data->screen, encoder, &patched );
}
