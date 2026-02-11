write(const float* buffer, size_t w, size_t h) {
	uint8_t* temp = 0;
	size_t n = w*h;
	temp = new uint8_t[n];
	for (size_t i=0;i<n;i++) {
		float x = buffer[i];
		if (x < 0 || x > 255) {
			std::cout << "Index: " << i << ", value: " << x << std::endl;
			throw std::runtime_error("Values outside [0,255]");
		}
		temp[i] = (uint8_t)x;
	}
	writer.write(temp, w, h);
	delete[] temp;
}
