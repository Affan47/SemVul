DefineLInput(float *x, int ht, int wt, int N_)
{


	if((class_state.INPUT_DEFINED)||(class_state.LATTICE_DEFINED))
		ResetInput();


	if(((height	= ht) <= 0)||((width	= wt) <= 0))
	{
		ErrorHandler("MeanShift", "DefineLInput", "Lattice defined using zero or negative height and/or width.");
		return;
	}


	if((N = N_) <= 0)
	{
		ErrorHandler("MeanShift", "DefineInput", "Input defined using zero or negative dimension.");
		return;
	}


	L		= height*width;


	InitializeInput(x);


	if(ErrorStatus == EL_ERROR)
		return;


	if(!(weightMap = new float [L]))
	{
		ErrorHandler("MeanShift", "InitializeInput", "Not enough memory.");
		return;
	}


	memset(weightMap, 0, L*(sizeof(float)));


	class_state.LATTICE_DEFINED	= true;
	class_state.INPUT_DEFINED	= false;
	class_state.OUTPUT_DEFINED	= false;


	return;

}
