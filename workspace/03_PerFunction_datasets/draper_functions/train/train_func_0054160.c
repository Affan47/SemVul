position(string const searchtext,string const context,unsigned long long& result) {
		bool retval = false;
		result=0;
		size_t i = context.find(searchtext);
		if ( i < string::npos ) {
			retval = true;
			string::const_iterator l1=context.begin()+i;
			string::const_iterator f1=context.begin();
			while(f1 < l1) {
				if ((*f1 & 0x80) == 0x00) {
					f1++; result++;
				} else if ((*f1 & 0xe0) == 0xc0 && f1 + 1 != l1 && (f1[1] & 0xc0) == 0x80) {
					f1 += 2; result++;
				}
				else if ((*f1 & 0xf0) == 0xe0 && f1 + 1 != l1 && f1 + 2 != l1 && (f1[1] & 0xc0) == 0x80 && (f1[2] & 0xc0) == 0x80) {
					f1 += 3; result++;
				} else {
					return false;
				}
			}
		}
		return retval;
	}
