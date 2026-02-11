init() {

	create("skeleton key", 10, 3, MATERIAL_METAL, 0);
	create("lock pick", 20, 4, MATERIAL_METAL, 0);
	create("credit card", 10, 1, MATERIAL_METAL, 0);


	addToMap("key", _keys["skeleton key"]);


	create("Master Key of Thievery", 3500, 3, MATERIAL_METAL, PROPERTY_ARTIFACT);
}
