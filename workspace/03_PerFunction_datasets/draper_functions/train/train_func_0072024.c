remove_sensor(unsigned int id) throw(const char *) {
	std::map<unsigned int, Sensor*>::iterator iter;
	if ((iter = sensor_map.find((0x0000FFFF & id))) != sensor_map.end()) {
		sensor_map.erase(iter);
		delete(iter->second);
	} else throw "remove_sensor(): no such sensor";
}
