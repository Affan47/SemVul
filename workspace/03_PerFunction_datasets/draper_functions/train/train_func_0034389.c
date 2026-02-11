operator*=(const matrix &p_matrix){
	matrix product;
	for (size_t i = 0; i < 4; i++){
		for (size_t j = 0; j < 4; j++){
			double sum = 0;
			for (size_t k = 0; k < 4; k++){
				sum += (*this)[i][k] * (p_matrix[k][j]);
			}
			product[i][j] = sum;
		}
	}
	*this = std::move(product);
	return *this;
}
