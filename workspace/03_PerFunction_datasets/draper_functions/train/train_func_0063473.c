wrapString(const QString &str, int wid)
{
	QStringList lines;
	QString cur;
	QString tmp = str;

	while(1) {
		QString word = getNext(&tmp);
		if(word == QString::null) {
			lines += cur;
			break;
		}

		if(!cur.isEmpty()) {
			if((int)cur.length() + (int)word.length() > wid) {
				lines += cur;
				cur = "";
			}
		}
		if(cur.isEmpty()) {

			for(int n = 0; n < (int)word.length(); ++n) {
				if(!word.at(n).isSpace()) {
					if(n > 0) {
						word = word.mid(n);
					}
					break;
				}
			}
		}
		cur += word;
	}
	return lines;
}
