calibOctant(float32_t *vec) {
	float32_t x, y, z;

	x = vec[0] + calibData.bias[0];
	y = vec[1] + calibData.bias[1];
	z = vec[2] + calibData.bias[2];

	if (x > 0) {
		if (y > 0) {
			if (z > 0) {
				return 0;
			} else {
				return 1;
			}
		} else {
			if (z > 0) {
				return 2;
			} else {
				return 3;
			}
		}
	} else {
		if (y > 0) {
			if (z > 0) {
				return 4;
			} else {
				return 5;
			}
		} else {
			if (z > 0) {
				return 6;
			} else {
				return 7;
			}
		}
	}
}
