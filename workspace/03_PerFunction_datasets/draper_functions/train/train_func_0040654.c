blank(char visited[], int blanks)
	{
		for(int i = 0; i < blanks / 2; ++i) {
			int index1 = rand() % 81;
			int index2 = 80 - index1;

			while(visited[index1] == 0 || visited[index2] == 0) {
				index1 = rand() % 81;
				index2 = 80 - index1;
			}
			visited[index1] = 0;
			visited[index2] = 0;
		}
		return 0;
	}
