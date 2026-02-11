print(int w, int p) const
{
	int i;

	for(i = 0; i < 2; i++){
		cout << setw(w) << setprecision(p) << Round(row[i].x, p) << " ";
		cout << setw(w) << setprecision(p) << Round(row[i].y, p);
		cout << endl;
	}
}
