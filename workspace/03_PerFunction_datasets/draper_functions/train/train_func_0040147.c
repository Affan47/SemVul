constradict(int x,int y, BOX * blk){
int x1 = blk->ll.x;
int y1 = blk->ll.y;
int x2 = blk->ur.x;
int y2 = blk->ur.y;

	if( x>x1 && x<x2 && y > y1 && y < y2){
		printf("error, blk is in the blockage\n");
		exit(0);
	}

	else if ( x < x1 || x > x2 || y < y1 || y > y2)
		return 0;
	else {
		if ( x == x1 && y >= y1 && y <= y2){
			if (frame.ll.x < x1)
				return 3;
		}
		else if ( y == y1 && x >= x1 && x <= x2){
			if (frame.ll.y < y1)
				return 2;
		}
		else if ( x == x2 && y >= y1 && y <= y2){
			if (frame.ur.x > x2)
				return 4;
		}
		else if ( y == y2 && x >= x1 && x <= x2){
			if (frame.ur.y > y2)
				return 1;
		}
		else {
			printf(" wrong type of node\n");
			exit(0);
		}
	}

	printf(" another wrong type of node\n");
	exit(0);
}
