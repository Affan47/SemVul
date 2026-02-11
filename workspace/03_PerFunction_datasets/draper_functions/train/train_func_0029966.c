putTyVar(n)
Int n; {
    static String alphabet
		="abcdefghijklmnopqrstuvwxyz";
    putChr(alphabet[n%26]);
    if (n /= 26)
	putInt(n);
}
