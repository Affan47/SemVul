dump_array16(int array[],int size){
	int i;
	--size;
	for (i = 0; i < size; ++i) {
		printf("0x%04x, ", array[i]);
		if(!((i+1)&0x7))
			printf("\n  ");
	}
	printf("0x%04x\n};\n\n", array[size]);
}
