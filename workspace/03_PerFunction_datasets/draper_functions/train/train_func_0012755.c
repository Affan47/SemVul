multi_get_new_id()
{
	if(Multi_id_num > 20000){
		Multi_id_num = 0;
	}

	return Multi_id_num++;
}
