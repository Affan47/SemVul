setBloodMaterialNumbers(uint32_t *numbers)
{
	for(int i = 0; i < 3; i++)
		mBloodMaterials[i] = numbers[i];
}
