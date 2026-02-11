delete_files() {
	if(is_open())
		close();

	if(file_name){
		delete_file(file_name, PA_SDBM_DIRFEXT);
		delete_file(file_name, PA_SDBM_PAGFEXT);
	}
}
