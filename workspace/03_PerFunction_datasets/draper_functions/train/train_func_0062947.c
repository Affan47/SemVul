add_attribute(string name, string value) {
	xmlAttribute A;
	A.name = name;
	A.value = value;
	return add_attribute(A);
}
