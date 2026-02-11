Neo_Hookean_init(mode,mi)
int mode;
struct method_instance *mi;
{

  if ( web.modeltype != LINEAR )
     kb_error(2819,"Neo_Hookean method only for LINEAR model.\n",RECOVERABLE);

  if ( web.dimension != 2 )
     kb_error(2829,"Neo_Hookean method only for SOAPFILM model.\n",
        RECOVERABLE);


  lambda_attr = find_attribute(FACET,NEO_LAMBDA_NAME);
  if ( lambda_attr < 0 )
     kb_error(2837,"Facet extra attribute neo_lambda missing. Needed by Neo_Hookean.\n",RECOVERABLE);
  mu_attr = find_attribute(FACET,NEO_MU_NAME);
  if ( mu_attr < 0 )
     kb_error(2838,"Facet extra attribute neo_mu missing. Needed by Neo_Hookean.\n",RECOVERABLE);

  form_factors_attr = find_attribute(FACET,FORM_FACTORS_NAME);
  if ( form_factors_attr < 0 )
     kb_error(2839,"Facet extra attribute form_factors real[3] missing. Needed by Neo_Hookean.\n",RECOVERABLE);

  if ( EXTRAS(FACET)[form_factors_attr].array_spec.datacount != 3 )
     kb_error(2850,"Facet extra attribute form_factors must have size 3.\n",
        RECOVERABLE);
}
