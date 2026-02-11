Clear() {
	for (int i = 0; i < MAXTAG; i++) {
		delete []pat[i];
		pat[i] = 0;
		bopat[i] = NOTFOUND;
		eopat[i] = NOTFOUND;
	}
}
