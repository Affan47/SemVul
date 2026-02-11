load(ifstream & fp){
				uint r = loadValue<uint>(fp);
				size_t pos = fp.tellg();
				fp.seekg(pos-sizeof(uint));
				switch(r) {
					case CSA_HDR: return TextIndexCSA::load(fp);
				}
				return NULL;
			}
