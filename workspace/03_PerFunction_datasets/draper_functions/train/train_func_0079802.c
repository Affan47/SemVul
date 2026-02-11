destroy_PT_sequence(PT_sequence *obj){
	if (obj->mh.parent) {
		aisc_unlink((dllheader_ext*)obj);
		if (aisc_server_error) return;
	}
	if(obj->mh.ident)	free(obj->mh.ident);
			if(obj->seq.data) free(obj->seq.data);
	free((char *)obj);
}
