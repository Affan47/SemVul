serialize_xml(struct dynvVariable* variable, ostream& out){
	if (variable->ptr_value){
		float* color = (float*)variable->ptr_value;
		out << color[0] <<" "<< color[1] <<" "<< color[2] <<" "<< color[3];
	}
	return 0;
}
