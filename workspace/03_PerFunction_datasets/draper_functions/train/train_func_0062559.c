indent(int level, Writer *writer) {
	if (!isFormatted || level<=0) return;
	writer->write("\n");
	writer->write(string(INDENT * level, ' '));
}

}
