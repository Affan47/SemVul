IsOctaveComment(Accessor &styler, int pos, int len) {
	return len > 0 && IsOctaveCommentChar(styler[pos]) ;
}
