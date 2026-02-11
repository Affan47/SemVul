stop_block() throw(fatal_exception) {
			unsigned ret = block_expected.top();
			block_expected.pop();
			return ret;
		}
