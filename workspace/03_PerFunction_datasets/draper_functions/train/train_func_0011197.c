operator==(const CL_Matrix4x4 &other) const
{
	for (int i=0; i<16; i++)
		if (matrix[i] != other.matrix[i]) return false;
	return true;
}
