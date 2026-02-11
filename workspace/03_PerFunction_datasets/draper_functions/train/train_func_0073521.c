setHorizontalAlignment(char h, col_type col)
{
	colinfo_[col].align_ = h;
	if (!colinfo_[col].special_.empty()) {
		char_type & c = colinfo_[col].special_[colinfo_[col].special_.size() - 1];
		if (c == 'l' || c == 'c' || c == 'r')
			c = h;
	}

}
