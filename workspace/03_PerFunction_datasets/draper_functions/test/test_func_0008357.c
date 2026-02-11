readReasonPhrase(size_t pos, size_t endLinePos) {
		header.reasonPhrase = headerString.substr(pos, endLinePos-pos);
		return nextLine(endLinePos);
	}
