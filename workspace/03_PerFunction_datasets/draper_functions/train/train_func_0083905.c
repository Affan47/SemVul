gerbv_image_copy_image (gerbv_image_t *sourceImage, gerbv_user_transformation_t *transform, gerbv_image_t *destinationImage) {
    int lastUsedApertureNumber = APERTURE_MIN - 1;
    int i;
    GArray *apertureNumberTable = g_array_new(FALSE,FALSE,sizeof(gerb_translation_entry_t));


    for (i = 0; i < APERTURE_MAX; i++) {
	if (sourceImage->aperture[i] != NULL) {
	  gint existingAperture = gerbv_image_find_existing_aperture_match (sourceImage->aperture[i], destinationImage);


	  if (existingAperture > 0) {
	  	gerb_translation_entry_t translationEntry={i,existingAperture};
	 	g_array_append_val (apertureNumberTable,translationEntry);
	  }

	  else {
	  	gerbv_aperture_t *newAperture = gerbv_image_duplicate_aperture (sourceImage->aperture[i]);

	  	lastUsedApertureNumber = gerbv_image_find_unused_aperture_number (lastUsedApertureNumber + 1, destinationImage);

	  	gerb_translation_entry_t translationEntry={i,lastUsedApertureNumber};
	  	g_array_append_val (apertureNumberTable,translationEntry);

	  	destinationImage->aperture[lastUsedApertureNumber] = newAperture;
	  }
	}
    }

    gerbv_netstate_t *lastState;
    gerbv_layer_t *lastLayer;
    gerbv_net_t *lastNet;

    for (lastState = destinationImage->states; lastState->next; lastState=lastState->next){}
    for (lastLayer = destinationImage->layers; lastLayer->next; lastLayer=lastLayer->next){}
    for (lastNet = destinationImage->netlist; lastNet->next; lastNet=lastNet->next){}


    gerbv_image_copy_all_nets (sourceImage, destinationImage, lastLayer, lastState, lastNet, transform, apertureNumberTable);
    g_array_free (apertureNumberTable, TRUE);
}
