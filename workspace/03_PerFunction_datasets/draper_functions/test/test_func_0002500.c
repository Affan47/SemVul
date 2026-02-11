zDNAScoreISOFeature (zScanner *scanner, zSfeature *f) {
	float gc;
	int i;

	gc = zGetDNAWindowedGC(scanner->seq->parent,(int)((f->start+f->end)/2));
	i = 0;
	while (gc > scanner->model->data[i] && i < scanner->model->submodels-1) i++;


	return scanner->subscanner[i].scoref(&scanner->subscanner[i], f);
}
