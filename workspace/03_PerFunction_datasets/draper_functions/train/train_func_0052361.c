print()
{
    do {
	exprintln();
	writeline(-1, 0, low);
	low = fseekeol(low) + 1;
    } while (low < high);
    exprintln();
}
