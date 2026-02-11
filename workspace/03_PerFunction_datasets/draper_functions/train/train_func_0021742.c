m_ScaleScreen (Object *in, Object *out)
{
  float factor;
  int final_res;
  Object incopy=NULL;
  Camera new_camera;

  if (!in[0])
    {
      DXSetError(ERROR_BAD_PARAMETER, "object must be specified");
      goto error;
    }

  if ((DXGetObjectClass(in[0]) != CLASS_STRING) &&
      (DXGetObjectClass(in[0]) != CLASS_ARRAY))
  {
     incopy = DXCopy(in[0], COPY_STRUCTURE);
     if (!incopy)
        goto error;
  }
  else
  {
     DXSetError(ERROR_MISSING_DATA,"object must be specified");
     goto error;
  }

  if (!incopy && !in[2])
    {
      out[0] = incopy;
      out[1] = in[3];
      return OK;
    }

  if (in[1])
   if (!DXExtractFloat(in[1], &factor))
    {
      DXSetError(ERROR_BAD_PARAMETER, "scale_factor must be a scalar value");
      goto error;
    }

  if (in[2])
    if (!DXExtractInteger(in[2], &final_res))
    {
      DXSetError(ERROR_BAD_PARAMETER, "final_res must be an integer");
      goto error;
    }

  if (in[1] && in[2])
    {
      DXWarning("both scale_factor and final_res are specified. Only scale_factor will be used");
    }

  if (in[3])
    {
      if ((DXGetObjectClass(in[3]) != CLASS_CAMERA))
	{
	  DXSetError(ERROR_BAD_PARAMETER,"current_camera must be a camera");
	  goto error;
	}
    }

  if (!in[1] && in[2] && !in[3])
    {
      DXSetError(ERROR_DATA_INVALID,"if final_res is specified, current_camera must be specified");
      goto error;
    }


  if (!in[1]){
     if (in[3]) {
         if (!GetFactor(final_res, (Camera)in[3], &factor))
            goto error;
     }
     else {
       factor = 1;
     }
  }

  if (!TraverseToScreen(incopy, factor))
    goto error;

  out[0] = incopy;


  if (in[3])
    {
      new_camera = MakeNewCamera((Camera)in[3], factor);
      if (!new_camera)
      {
        goto error;
      }
      out[1] = (Object)new_camera;
    }
  else
    out[1] = NULL;


  return OK;
 error:
  DXDelete((Object)incopy);
  return ERROR;
}
