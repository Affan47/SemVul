SimpleExecute (vtkImageData *input, vtkImageData *output)
{
	void* inPtr = input->GetScalarPointer();
	void* outPtr = output->GetScalarPointer();
	switch (input->GetScalarType())
	{
		vtkTemplateMacro(vtkImageDataCleanLabelsExecute(input, output,
										(VTK_TT*)(inPtr), (VTK_TT*)(outPtr)));
	default:
		vtkGenericWarningMacro("ThreadedRequestData: Unknown output ScalarType");
		return;
	}
}
