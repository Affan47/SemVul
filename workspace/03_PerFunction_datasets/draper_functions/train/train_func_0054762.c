sleq(int8 *s1, int8 *s2) {

	if(!s1[0] && !s2[0]) {
		return 1;
	}

	if (s1[0] < s2[0]) return 1;
	if (s1[0] > s2[0]){
		printf("$%d, %d$ (zero)\n", s1[0], s2[0]);
		return 0;
	}

	int temp = sleq(s1+1, s2+1);

	if(!temp)
		printf("$%d, %d$\n", s1[0], s2[0]);

return temp;
}
