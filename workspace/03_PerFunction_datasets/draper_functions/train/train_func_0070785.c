get_model_name(char *iProduct, char *iModel)
{
  models_name_t *model = NULL;

  upsdebugx(2, "get_model_name(%s, %s)\n", iProduct, iModel);


  for ( model = models_names ; model->iProduct != NULL ; model++ )
	{
	  upsdebugx(2, "comparing with: %s", model->finalname);
	  if ( (!strncmp(iProduct, model->iProduct, strlen(model->iProduct)))
		   && (!strncmp(iModel, model->iModel, strlen(model->iModel))) )
		{
		  upsdebugx(2, "Found %s\n", model->finalname);
		  break;
		}
	}


  return model->finalname;
}
