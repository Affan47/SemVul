setVertVector(int row, int col, const GLEPoint3D& p) {
	int idx = row*m_Cols+col;
	for (int pos = 0; pos < 3; pos++) {
		m_C[idx] = p.m_C[pos];
		idx += m_Cols;
	}
}
