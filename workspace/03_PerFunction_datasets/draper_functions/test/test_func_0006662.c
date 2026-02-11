save_yank(FILE *f)
{
	UNDOREC *rec;
	for (rec = yanked.link.next; rec != &yanked; rec = rec->link.next) {
		if (rec->len < SMALL) {
			fprintf(f,"	");
			emit_string(f,rec->small,rec->len);
			fprintf(f,"\n");
		}
	}
	fprintf(f,"done\n");
}
