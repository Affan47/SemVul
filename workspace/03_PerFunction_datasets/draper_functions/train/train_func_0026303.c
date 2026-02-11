adjust_buf_node(BUF_NODE * bt, BLOCKAGE * block,int num){
int direct = -1;
	check_buf_node(bt,block,num,&direct);
	switch(direct){
		case 1:
				(bt->y) += 0.1;
				break;
		case 2:
				(bt->y) -= 0.1;
				break;
		case 3:
				(bt->x) -= 0.1;
				break;
		case 4:
				(bt->x) += 0.1;
				break;
		default:
				break;
	}
	return;

}
