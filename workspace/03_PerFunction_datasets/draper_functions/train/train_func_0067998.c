open_OBJ(const std::string &p_path){
	mesh ret;
	std::ifstream file(p_path, std::ios::binary | std::ios::in);
	std::string tmp;
	while (file>>tmp){
		if (tmp == "v"){
			double a, b, c;
			file >> a >> b >> c;
			ret.vertices.push_back(vertex(point3d(a, b, c)));
		}
		if (tmp == "f"){
			std::string a, b, c;
			file >> a >> b >> c;
			ret.indices.push_back(std::stoi(a) - 1);
			ret.indices.push_back(std::stoi(b) - 1);
			ret.indices.push_back(std::stoi(c) - 1);
		}
	}
	return ret;
}
