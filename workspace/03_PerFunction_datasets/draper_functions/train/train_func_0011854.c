estimateImageBias(VimosImage *image, VimosPort *port)
{
  const char       modName[] = "estimateImageBias";
  VimosPort       *currentPort;
  VimosBool        success;
  VimosFloatArray *biasLevel;
  float           *bias;
  float            prscBiasLevel, ovscBiasLevel;
  int              sizePrsc;
  int              sizeOvsc;
  int              nPorts = 0;
  int              i = 0;

  if (!(image && port)) {
    cpl_msg_debug(modName, "NULL input(s)");
    return NULL;
  }

  for (currentPort = port; currentPort; currentPort = currentPort->next)
    nPorts++;

  if (!(biasLevel = newFloatArray(nPorts))) {
    cpl_msg_debug(modName, "Cannot allocate output");
    return NULL;
  }

  for (currentPort = port; currentPort; currentPort = currentPort->next) {
    success = VM_FALSE;

    sizePrsc = 0;
    sizeOvsc = 0;

    if (currentPort->prScan->nX > 0) {


      bias = extractFloatImage(image->data, image->xlen, image->ylen,
             currentPort->prScan->startX, currentPort->prScan->startY,
             currentPort->prScan->nX, currentPort->prScan->nY);

      if (!bias) {
        cpl_msg_debug(modName, "Memory allocation failure");
        return NULL;
      }

      sizePrsc = currentPort->prScan->nX * currentPort->prScan->nY;
      prscBiasLevel = computeAverageFloat(bias, sizePrsc);
      pil_free(bias);
      success = VM_TRUE;
    }
    else {
      prscBiasLevel = 0.;
    }

    if (currentPort->ovScan->nX > 0) {


      bias = extractFloatImage(image->data, image->xlen, image->ylen,
             currentPort->ovScan->startX, currentPort->ovScan->startY,
             currentPort->ovScan->nX, currentPort->ovScan->nY);

      if (!bias) {
        cpl_msg_debug(modName, "Memory allocation failure");
        return NULL;
      }

      sizeOvsc = currentPort->ovScan->nX * currentPort->ovScan->nY;
      ovscBiasLevel = computeAverageFloat(bias, sizeOvsc);
      pil_free(bias);
      success = VM_TRUE;
    }
    else {
      ovscBiasLevel = 0.;
    }

    if (success) {
      biasLevel->data[i] =
                   (prscBiasLevel * sizePrsc + ovscBiasLevel * sizeOvsc)
                   / (sizePrsc + sizeOvsc);
      i++;
    }

  }

  if (i != nPorts) {
    deleteFloatArray(biasLevel);
    return(NULL);
  }

  return(biasLevel);

}
