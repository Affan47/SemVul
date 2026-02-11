gerbv_image_verify(gerbv_image_t const* image)
{
    gerb_verify_error_t error = GERB_IMAGE_OK;
    int i, n_nets;;
    gerbv_net_t *net;

    if (image->netlist == NULL) error |= GERB_IMAGE_MISSING_NETLIST;
    if (image->format == NULL)  error |= GERB_IMAGE_MISSING_FORMAT;
    if (image->info == NULL)    error |= GERB_IMAGE_MISSING_INFO;


    n_nets = 0;
    if (image->netlist != NULL) {
      for (net = image->netlist->next ; net != NULL; net = net->next) {
	n_nets++;
      }
    }


    if( n_nets > 0) {
      for (i = 0; i < APERTURE_MAX && image->aperture[i] == NULL; i++);
      if (i == APERTURE_MAX) error |= GERB_IMAGE_MISSING_APERTURES;
    }

    return error;
}
