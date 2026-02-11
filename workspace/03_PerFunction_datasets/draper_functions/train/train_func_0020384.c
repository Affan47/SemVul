model_update_instance(int model_instance_num, int sub_model_num, submodel_instance_info *sii)
{
	int i;
	polymodel *pm;
	polymodel_instance *pmi;

	pmi = model_get_instance(model_instance_num);
	pm = model_get(pmi->model_num);

	Assert( sub_model_num >= 0 );
	Assert( sub_model_num < pm->n_models );

	if ( sub_model_num < 0 ) return;
	if ( sub_model_num >= pm->n_models ) return;

	submodel_instance *smi = &pmi->submodel[sub_model_num];
	bsp_info *sm = &pm->submodel[sub_model_num];


	smi->blown_off = sii->blown_off ? true : false;

	if ( smi->blown_off )	{
		if ( sm->my_replacement > -1 )	{
			pmi->submodel[sm->my_replacement].blown_off = false;
			pmi->submodel[sm->my_replacement].angs = sii->angs;
			pmi->submodel[sm->my_replacement].prev_angs = sii->prev_angs;
		}
	} else {


		if ( sm->my_replacement > -1 && sm->my_replacement != sub_model_num)	{
			pmi->submodel[sm->my_replacement].blown_off = true;
		}
	}


	smi->angs = sii->angs;
	smi->prev_angs = sii->prev_angs;


	for (i=0; i<sm->num_details; i++ )	{
		model_update_instance(model_instance_num, sm->details[i], sii );
	}
}
