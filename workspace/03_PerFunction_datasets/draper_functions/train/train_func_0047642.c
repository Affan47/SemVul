touch() {
	if (file.open(QFile::WriteOnly)) {
		file.write("a");
		file.close();
		return true;
	}

	return false;
}
