DisplayVerticesColors (vtkIntArray * Scalars)
{
	if (Scalars)
		this->Input->GetPointData ()->SetScalars (Scalars);

	int i;
	int max = 0;

	for (i = 0; i < this->Input->GetNumberOfPoints (); i++)
	{
		if (max < Scalars->GetValue (i))
			max = Scalars->GetValue (i);
	}
	this->DisplayRandomColors(max);
}
