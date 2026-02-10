ao_device_load_options(ao_device *device, ao_option *options){

  while (options != NULL) {
    if(!strcmp(options->key,"matrix")){


      if(device->output_matrix)
        free(device->output_matrix);


      device->output_matrix = _sanitize_matrix(32, options->value, device);
      if(!device->output_matrix){
        aerror("Empty or inavlid output matrix\n");
        return AO_EBADOPTION;
      }
      adebug("Sanitized device output matrix: %s\n",device->output_matrix);
    }else if(!strcmp(options->key,"debug")){
      device->verbose=2;
    }else if(!strcmp(options->key,"verbose")){
      if(device->verbose<1)device->verbose=1;
    }else if(!strcmp(options->key,"quiet")){
      device->verbose=-1;
    }else{
      if (!device->funcs->set_option(device, options->key, options->value)) {

        return AO_EOPENDEVICE;
      }
    }

    options = options->next;
  }

  return 0;
}
