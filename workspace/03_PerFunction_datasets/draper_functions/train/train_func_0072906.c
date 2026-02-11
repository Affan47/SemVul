intersection(const Ray &ray, IntInfo &info, std::string &obj)
{
	IntInfo test, res;

	std::map<std::string, Object *>::iterator it;
	for (it = m_objects.begin(); it != m_objects.end(); it++) {

		if((m_geometry[(*it).second->geometry.c_str()])->intersection(ray, &test)) {
			if(res.t > test.t) {

				obj = (*it).first;


				memcpy(&res, &test, sizeof(res));
			}
		}
	}


	memcpy(&info, &res, sizeof(info));

	return info.t != INFINITY ? true : false;
}
