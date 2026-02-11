vector3_multiply_matrix3x3(const vector3* vector, const matrix3x3* matrix, vector3* result) {

	vector3 vector_t;

	if (vector==result){
		vector3_copy(vector, &vector_t);
		vector=&vector_t;
	}

	result->x = vector->x * matrix->m[0][0] + vector->y * matrix->m[0][1] + vector->z * matrix->m[0][2];
	result->y = vector->x * matrix->m[1][0] + vector->y * matrix->m[1][1] + vector->z * matrix->m[1][2];
	result->z = vector->x * matrix->m[2][0] + vector->y * matrix->m[2][1] + vector->z * matrix->m[2][2];
}
