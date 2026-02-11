getRandomSet(int sampleSize, int setSize){
	if(sampleSize<setSize){
		printf("Set size too small in RANSAC\n");
		exit(0);
	}
	vector<int> lista;
	for(int i=0;i<sampleSize;i++){
		lista.push_back(i);
	}
	vector<int> randomSet;
	while(randomSet.size()<setSize){
		int pos = rand()%lista.size();
		randomSet.push_back(lista[pos]);
		lista.erase(lista.begin()+pos);
	}


	return randomSet;

}
