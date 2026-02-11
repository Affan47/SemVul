AllocateMatrices(int Size)
	{
		this->FreeMatrices();

		SecondMember = new double * [Size];
		VandermondeMatrix = new double * [Size];
		for (i = 0; i < Size; i++)
		{
			VandermondeMatrix[i] = new double[6];
			SecondMember[i]= new double;
		}

		this->MatricesSize=Size;
	}
