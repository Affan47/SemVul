load(ifstream & input) {
        uint rd;
        input.read((char*)&rd,sizeof(uint));
        size_t pos = input.tellg();
        input.seekg(pos-sizeof(uint));
        switch(rd) {
            case MAPPER_NONE_HDR: return MapperNone::load(input);
            case MAPPER_CONT_HDR: return MapperCont::load(input);
        }
        return NULL;
    }
